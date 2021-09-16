#include "Object.h"
#include "Function.h"

Object::Object(std::map<std::string, Type*>& variables, std::vector<std::string>& instances) : Type(OBJECT)
{
	// copy variables and methods
	for (const std::pair<std::string, Type*>& pair : variables)
	{
		this->_variables[pair.first] = pair.second->useValue();
		if (this->_variables[pair.first]->getType() == FUNCTION)
			((Function*)this->_variables[pair.first])->setThis(new Reference(this), false);
		else if (this->_variables[pair.first]->getType() == STATIC_FUNCTION)
			((StaticFunction*)this->_variables[pair.first])->setThis(this, false);
	}
	// copy instances
	for (const std::string& instance : instances)
		this->_instances.push_back(instance);
}

Object::Object(Pair* pair) : Type(OBJECT)
{
	this->_variables[this->toName(pair->_first)] = pair->_second->useValue();
	delete pair;
}

Object::Object(short type) : Type(type)
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
	std::string result = "";
	if (!this->_instances.empty())
		result = this->_instances.back() + " ";
	if (this->_variables.size() == 0)
		return result + "{}";
	result += "{";
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
	return new Object(this->_variables, this->_instances);
}

void Object::toMethods()
{
	for (const std::pair<std::string, Type*>& pair : this->_variables)
	{
		if (pair.second->getType() == FUNCTION)
			((Function*)pair.second)->setThis(new Reference(this));
		else if (pair.second->getType() == STATIC_FUNCTION)
			((StaticFunction*)pair.second)->setThis(this, false);
	}
}

std::map<std::string, Type*>& Object::getVariables()
{
	return this->_variables;
}

std::vector<std::string>& Object::getInstances()
{
	return this->_instances;
}

Type* Object::index(Type* other)
{
	if (((List*)other)->getContent().size() > 0)
	{
		if (this->_variables.find(this->toName(((List*)other)->getContent()[0], false)) != this->_variables.end())
		{
			Type* value = this->_variables[this->toName(((List*)other)->getContent()[0], false)];
			return this->isVariable() ? new Reference(value) : value->useValue();
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
		return this->isVariable() ? new Reference(value) : value->useValue();
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
		// copy variables
		for (std::pair<const std::string, Type*>& pair : ((Object*)other)->_variables)
			this->_variables[pair.first] = pair.second->useValue();
		// copy instances
		for (const std::string& instance : ((Object*)other)->_instances)
			this->_instances.push_back(instance);
		return this;
	}
	else
		return Type::assign(other);
}

Type* Object::extend(Type* other)
{
	if (other->getType() == OBJECT || other->getType() == CLASS)
	{
		Object* copy = (Object*)this->useValue();
		// copy variables
		for (const std::pair<std::string, Type*>& pair : ((Object*)other)->_variables)
			copy->_variables[pair.first] = pair.second->useValue();
		// copy instances
		for (const std::string& instance : ((Object*)other)->_instances)
			copy->_instances.push_back(instance);
		return copy;
	}
	else if (other->getType() == PAIR)
	{
		Object* copy = (Object*)this->useValue();
		copy->_variables[this->toName(((Pair*)other)->_first)] = ((Pair*)other)->_second->useValue();
		return copy;
	}
	else
		return Type::extend(other);
}

Type* Object::extendAssign(Type* other)
{
	if (other->getType() == OBJECT || other->getType() == CLASS)
	{
		// copy variables
		for (const std::pair<std::string, Type*>& pair : ((Object*)other)->_variables)
			this->_variables[pair.first] = pair.second->useValue();
		// copy instances
		for (const std::string& instance : ((Object*)other)->_instances)
			this->_instances.push_back(instance);
		return this;
	}
	else if (other->getType() == PAIR)
	{
		this->_variables[this->toName(((Pair*)other)->_first)] = ((Pair*)other)->_second->useValue();
		return this;
	}
	else
		return Type::extend(other);
}

Type* Object::add(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("+");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::add(other);
}

Type* Object::sub(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("-");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::sub(other);
}

Type* Object::div(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("/");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::div(other);
}

Type* Object::mul(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("*");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::mul(other);
}

Type* Object::mod(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("mod");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::mod(other);
}

Type* Object::exp(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("**");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::exp(other);
}

Type* Object::increment(bool post)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("++");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(new Undefined());
	}
	else
		Type::increment(post);
}

Type* Object::decrement(bool post)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("--");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(new Undefined());
	}
	else
		Type::decrement(post);
}

Type* Object::ternary(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("?");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::ternary(other);
}

Type* Object::bitXor(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("^");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::bitXor(other);
}

Type* Object::bitAnd(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("&");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::bitAnd(other);
}

Type* Object::bitOr(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("|");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::bitOr(other);
}

Type* Object::bitNot()
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("~");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(new Undefined());
	}
	else
		Type::bitNot();
}

Type* Object::leftShift(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("<<");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::leftShift(other);
}

Type* Object::rightShift(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find(">>");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::rightShift(other);
}

Type* Object::call(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("()");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::call(other);
}

Type* Object::negative()
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("-");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(new Undefined());
	}
	else
		Type::negative();
}

Type* Object::addAssign(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("+=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::addAssign(other);
}

Type* Object::subAssign(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("-=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::subAssign(other);
}

Type* Object::divAssign(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("/=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::divAssign(other);
}

Type* Object::mulAssign(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("*=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::mulAssign(other);
}

Type* Object::modAssign(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("%=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::modAssign(other);
}

Type* Object::expAssign(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("**=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::expAssign(other);
}

Type* Object::xorAssign(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("^=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::xorAssign(other);
}

Type* Object::andAssign(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("&=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::andAssign(other);
}

Type* Object::orAssign(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("|=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::orAssign(other);
}

Type* Object::leftShiftAssign(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("<<=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::leftShiftAssign(other);
}

Type* Object::rightShiftAssign(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find(">>=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::rightShiftAssign(other);
}

Type* Object::equal(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("==");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::equal(other);
}

Type* Object::notEqual(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("!=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::notEqual(other);
}

Type* Object::greater(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find(">");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::greater(other);
}

Type* Object::less(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("<");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::less(other);
}

Type* Object::greaterEqual(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find(">=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::greaterEqual(other);
}

Type* Object::lessEqual(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("<=");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::lessEqual(other);
}

Type* Object::logicOr(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("||");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::logicOr(other);
}

Type* Object::logicAnd(Type* other)
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("&&");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(other);
	}
	else
		Type::logicAnd(other);
}

Type* Object::logicNot()
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("!");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(new Undefined());
	}
	else
		Type::logicNot();
}

Type* Object::toInt()
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("int");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(new Undefined());
	}
	else
		Type::toInt();
}

Type* Object::toBool()
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("bool");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(new Undefined());
	}
	else
		Type::toBool();
}

Type* Object::toFloat()
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("float");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(new Undefined());
	}
	else
		Type::toFloat();
}

Type* Object::toChar()
{
	std::map<std::string, Type*>::iterator it = this->_variables.find("char");
	if (it != this->_variables.end())
	{
		if (it->second->getType() != FUNCTION)
			throw SyntaxException("Overloaded operator is not a function");
		else
			return ((Function*)it->second)->call(new Undefined());
	}
	else
		Type::toChar();
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
