#include "Object.h"
#include "Function.h"

Object::Object(std::map<std::string, Type*>& variables) : Type(OBJECT)
{
	for (const std::pair<std::string, Type*>& pair : variables)
	{
		this->_variables[pair.first] = pair.second->copy();
		if (this->_variables[pair.first]->getType() == FUNCTION)
		{
			((Function*)this->_variables[pair.first])->setThis(new Reference(this), false);
		}
	}
}

Object::Object(Pair* pair) : Type(OBJECT)
{
	this->_variables[this->toName(pair->_first)] = pair->_second->copy();
	delete pair;
}

Object::Object(const std::string& type) : Type(type)
{
}

Object::Object() : Type(OBJECT)
{
}

Object::~Object()
{
	for (const std::pair<std::string, Type*>& pair : this->_variables)
		delete this->_variables[pair.first];
}

std::string Object::toString() const
{
	std::string result = "{";
	for (const std::pair<std::string, Type*>& pair : this->_variables)
	{
		result += pair.first + ": " + pair.second->toString() + ", ";
	}
	result.pop_back();
	result.pop_back();
	return result + "}";
}

Type* Object::copy()
{
	return new Object(this->_variables);
}

void Object::toMethods()
{
	for (const std::pair<std::string, Type*>& pair : this->_variables)
		if (pair.second->getType() == FUNCTION)
			((Function*)pair.second)->setThis(new Reference(this));
}

Type* Object::index(Type* other)
{
	if (((List*)other)->getContent().size() > 0)
	{
		if (this->_variables.find(this->toName(((List*)other)->getContent()[0], false)) != this->_variables.end())
		{
			Type* value = this->_variables[this->toName(((List*)other)->getContent()[0], false)];
			return this->isVariable() ? new Reference(value) : value->copy();
		}
		else
			return new Undefined();
	}
	else throw SyntaxException("Invalid object index");
}

Type* Object::point(Type* other)
{
	if (this->_variables.find(this->toName(other)) != this->_variables.end())
	{
		Type* value = this->_variables[this->toName(other)];
		return this->isVariable() ? new Reference(value) : value->copy();
	}
	else
		return new Undefined();
}

Type* Object::assign(Type* other)
{
	if (other->getType() == OBJECT)
	{
		for (std::pair<const std::string, Type*>& pair : this->_variables)
			delete pair.second;
		this->_variables.clear();
		for (std::pair<const std::string, Type*>& pair : ((Object*)other)->_variables)
			this->_variables[pair.first] = pair.second->copy();
		return this;
	}
	else
		return Type::assign(other);
}

Type* Object::extend(Type* other)
{
	if (other->getType() == OBJECT || other->getType() == CLASS)
	{
		Object* copy = (Object*)this->copy();
		for (const std::pair<std::string, Type*>& pair : ((Object*)other)->_variables)
			copy->_variables[pair.first] = pair.second->copy();
		return copy;
	}
	else if (other->getType() == PAIR)
	{
		Object* copy = (Object*)this->copy();
		copy->_variables[this->toName(((Pair*)other)->_first)] = ((Pair*)other)->_second->copy();
		return copy;
	}
	else
		return Type::extend(other);
}

Type* Object::extendAssign(Type* other)
{
	if (other->getType() == OBJECT || other->getType() == CLASS)
	{
		for (const std::pair<std::string, Type*>& pair : ((Object*)other)->_variables)
			this->_variables[pair.first] = pair.second->copy();
		return this;
	}
	else if (other->getType() == PAIR)
	{
		this->_variables[this->toName(((Pair*)other)->_first)] = ((Pair*)other)->_second->copy();
		return this;
	}
	else
		return Type::extend(other);
}

std::string Object::toName(Type* type, bool checkVar)
{
	if (type->getType() == NAME)
		return ((Name*)type)->_name;
	else if (checkVar && type->isVariable())
		return type->getVariable();
	else
		return type->toString();
}
