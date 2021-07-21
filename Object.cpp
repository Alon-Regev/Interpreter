#include "Object.h"

Object::Object(std::map<std::string, Type*>& variables) : Type(OBJECT)
{
	for (const std::pair<std::string, Type*>& pair : variables)
		this->_variables[pair.first] = pair.second->copy();
}

Object::Object(Pair* pair) : Type(OBJECT)
{
	this->_variables[this->toName(pair->_first)] = pair->_second->copy();
	delete pair;
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

Type* Object::index(Type* other)
{
	if (((List*)other)->_content.size() > 0)
	{
		if (this->_variables.find(this->toName(((List*)other)->_content[0], false)) != this->_variables.end())
			return this->_variables[this->toName(((List*)other)->_content[0], false)]->copy();
		else
			return new Undefined();
	}
	else throw SyntaxException("Invalid object index");
}

Type* Object::point(Type* other)
{
	if (this->_variables.find(this->toName(other)) != this->_variables.end())
		return this->_variables[this->toName(other)]->copy();
	else
		return new Undefined();
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
