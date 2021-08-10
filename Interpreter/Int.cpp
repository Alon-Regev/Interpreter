#include "Int.h"

Int::Int(const std::string& value) : Type(INT)
{
	if (Int::isType(value))
		this->_value = std::stoi(value);
	else
		throw InvalidOperationException("casting value of \"" + value + "\" to int");
}
Int::Int(const int value) : Type(INT), _value(value) {}
Int::Int() : Type(INT), _value(INT_DEFAULT_VALUE) {}

std::string Int::toString() const
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

int Int::getValue()
{
	return this->_value;
}

Type* Int::add(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value + ((Int*)other)->_value);
	else if (other->getType() == FLOAT)
		return new Float(this->_value + ((Float*)other)->getValue());
	else
		Type::add(other);
}

Type* Int::sub(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value - ((Int*)other)->_value);
	else if (other->getType() == FLOAT)
		return new Float(this->_value - ((Float*)other)->getValue());
	else
		Type::sub(other);
}

Type* Int::mul(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value * ((Int*)other)->_value);
	else if (other->getType() == FLOAT)
		return new Float(this->_value * ((Float*)other)->getValue());
	else
		Type::mul(other);
}

Type* Int::negative()
{
	return new Int(-this->_value);
}

Type* Int::assign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value = ((Int*)other)->_value;
		return this;
	}
	else if (other->getType() == FLOAT)
	{
		this->_value = ((Float*)other)->getValue();
		return this;
	}
	else
		Type::assign(other);
}

Type* Int::equal(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value == ((Int*)other)->_value);
	else if (other->getType() == FLOAT)
		return new Bool(this->_value == ((Float*)other)->getValue());
	else
		Type::equal(other);
}

Type* Int::notEqual(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value != ((Int*)other)->_value);
	else if (other->getType() == FLOAT)
		return new Bool(this->_value != ((Float*)other)->getValue());
	else
		Type::notEqual(other);
}

Type* Int::greater(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value > ((Int*)other)->_value);
	else if (other->getType() == FLOAT)
		return new Bool(this->_value > ((Float*)other)->getValue());
	else
		Type::greater(other);
}

Type* Int::less(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value < ((Int*)other)->_value);
	else if (other->getType() == FLOAT)
		return new Bool(this->_value < ((Float*)other)->getValue());
	else
		Type::less(other);
}

Type* Int::greaterEqual(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value >= ((Int*)other)->_value);
	else if (other->getType() == FLOAT)
		return new Bool(this->_value >= ((Float*)other)->getValue());
	else
		Type::greaterEqual(other);
}

Type* Int::lessEqual(Type* other)
{
	if (other->getType() == INT)
		return new Bool(this->_value <= ((Int*)other)->_value);
	else if (other->getType() == FLOAT)
		return new Bool(this->_value <= ((Float*)other)->getValue());
	else
		Type::lessEqual(other);
}

Type* Int::toBool()
{
	return new Bool((bool)this->_value);
}

Type* Int::toFloat()
{
	return new Float((double)this->_value);
}

Type* Int::div(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value / ((Int*)other)->_value);
	else if (other->getType() == FLOAT)
		return new Float(this->_value / ((Float*)other)->getValue());
	else
		Type::div(other);
}
