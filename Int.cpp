#include "Int.h"

Int::Int(const std::string& value) : Type(INT)
{
	this->_value = std::stoi(value);
}
Int::Int(const int value) : Type(INT), _value(value) {}
Int::Int() : Type(INT), _value(INT_DEFAULT_VALUE) {}

std::string Int::toString()
{
	return std::to_string(this->_value);
}

Type* Int::copy()
{
	return new Int(this->_value);
}

bool Int::isType(const std::string& value)
{
	return std::regex_match(value, std::regex("\\d+"));
}

Type* Int::add(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value + ((Int*)other)->_value);
	else
		Type::add(other);
}

Type* Int::sub(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value - ((Int*)other)->_value);
	else
		Type::sub(other);
}

Type* Int::mul(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value * ((Int*)other)->_value);
	else
		Type::mul(other);
}

Type* Int::assign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value = ((Int*)other)->_value;
		return this;
	}
	else
		Type::assign(other);
}

Type* Int::equal(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value == ((Int*)other)->_value);
	else
		Type::equal(other);
}

Type* Int::notEqual(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value != ((Int*)other)->_value);
	else
		Type::notEqual(other);
}

Type* Int::greater(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value > ((Int*)other)->_value);
	else
		Type::greater(other);
}

Type* Int::less(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value < ((Int*)other)->_value);
	else
		Type::less(other);
}

Type* Int::greaterEqual(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value >= ((Int*)other)->_value);
	else
		Type::greaterEqual(other);
}

Type* Int::lessEqual(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value <= ((Int*)other)->_value);
	else
		Type::lessEqual(other);
}

Type* Int::div(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value / ((Int*)other)->_value);
	else
		Type::div(other);
}
