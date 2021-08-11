#include "Float.h"
#include "Float.h"

Float::Float(const std::string& value) : Type(FLOAT)
{
	if (Float::isType(value))
		this->_value = std::stod(value);
	else
		throw InvalidOperationException("casting value of \"" + value + "\" to float");
}

Float::Float(const double value) : Type(FLOAT), _value(value)
{
}

Float::Float() : Type(FLOAT), _value(0)
{
}

std::string Float::toString() const
{
	std::stringstream sstream;
	sstream << this->_value;
	return sstream.str();
}

Type* Float::copy()
{
	return new Float(this->_value);
}

bool Float::isType(const std::string& value)
{
	return std::regex_match(value, std::regex(R"((?=[\d\.]*?\d)\d*\.?\d*(e-?\d+)?)"));
}

double Float::getValue()
{
	return this->_value;
}

Type* Float::add(Type* other)
{
	if (other->getType() == FLOAT)
		return new Float(this->_value + ((Float*)other)->getValue());
	else if (other->getType() == INT)
		return new Float(this->_value + ((Int*)other)->getValue());
	else
		return Type::add(other);
}

Type* Float::sub(Type* other)
{
	if (other->getType() == FLOAT)
		return new Float(this->_value - ((Float*)other)->getValue());
	else if (other->getType() == INT)
		return new Float(this->_value - ((Int*)other)->getValue());
	else
		return Type::sub(other);
}

Type* Float::div(Type* other)
{
	if (other->getType() == FLOAT)
		return new Float(this->_value / ((Float*)other)->getValue());
	else if (other->getType() == INT)
		return new Float(this->_value / ((Int*)other)->getValue());
	else
		return Type::div(other);
}

Type* Float::mul(Type* other)
{
	if (other->getType() == FLOAT)
		return new Float(this->_value * ((Float*)other)->getValue());
	else if (other->getType() == INT)
		return new Float(this->_value * ((Int*)other)->getValue());
	else
		return Type::mul(other);
}

Type* Float::exp(Type* other)
{
	if (other->getType() == FLOAT)
		return new Float(pow(this->_value, ((Float*)other)->getValue()));
	else if (other->getType() == INT)
		return new Float(pow(this->_value, ((Int*)other)->getValue()));
	else
		return Type::exp(other);
}

Type* Float::negative()
{
	return new Float(-this->_value);
}

Type* Float::assign(Type* other)
{
	if (other->getType() == FLOAT)
	{
		this->_value = ((Float*)other)->getValue();
		return this;
	}
	else if (other->getType() == INT)
	{
		this->_value = ((Int*)other)->getValue();
		return this;
	}
	else
		Type::assign(other);
}

Type* Float::addAssign(Type* other)
{
	if (other->getType() == FLOAT)
	{
		this->_value += ((Float*)other)->getValue();
		return this;
	}
	else if (other->getType() == INT)
	{
		this->_value += ((Int*)other)->getValue();
		return this;
	}
	else
		Type::addAssign(other);
}

Type* Float::subAssign(Type* other)
{
	if (other->getType() == FLOAT)
	{
		this->_value -= ((Float*)other)->getValue();
		return this;
	}
	else if (other->getType() == INT)
	{
		this->_value -= ((Int*)other)->getValue();
		return this;
	}
	else
		Type::subAssign(other);
}

Type* Float::divAssign(Type* other)
{
	if (other->getType() == FLOAT)
	{
		this->_value /= ((Float*)other)->getValue();
		return this;
	}
	else if (other->getType() == INT)
	{
		this->_value /= ((Int*)other)->getValue();
		return this;
	}
	else
		Type::divAssign(other);
}

Type* Float::mulAssign(Type* other)
{
	if (other->getType() == FLOAT)
	{
		this->_value *= ((Float*)other)->getValue();
		return this;
	}
	else if (other->getType() == INT)
	{
		this->_value *= ((Int*)other)->getValue();
		return this;
	}
	else
		Type::mulAssign(other);
}

Type* Float::expAssign(Type* other)
{
	if (other->getType() == FLOAT)
	{
		this->_value = pow(this->_value, ((Float*)other)->getValue());
		return this;
	}
	else if (other->getType() == INT)
	{
		this->_value = pow(this->_value, ((Int*)other)->getValue());
		return this;
	}
	else
		Type::expAssign(other);
}

Type* Float::equal(Type* other)
{
	if (other->getType() == FLOAT)
		return new Bool(this->_value == ((Float*)other)->getValue());
	else if (other->getType() == INT)
		return new Bool(this->_value == ((Int*)other)->getValue());
	else
		return Type::equal(other);
}

Type* Float::notEqual(Type* other)
{
	if (other->getType() == FLOAT)
		return new Bool(this->_value != ((Float*)other)->getValue());
	else if (other->getType() == INT)
		return new Bool(this->_value != ((Int*)other)->getValue());
	else
		return Type::notEqual(other);
}

Type* Float::greater(Type* other)
{
	if (other->getType() == FLOAT)
		return new Bool(this->_value > ((Float*)other)->getValue());
	else if (other->getType() == INT)
		return new Bool(this->_value > ((Int*)other)->getValue());
	else
		return Type::greater(other);
}

Type* Float::less(Type* other)
{
	if (other->getType() == FLOAT)
		return new Bool(this->_value < ((Float*)other)->getValue());
	else if (other->getType() == INT)
		return new Bool(this->_value < ((Int*)other)->getValue());
	else
		return Type::less(other);
}

Type* Float::greaterEqual(Type* other)
{
	if (other->getType() == FLOAT)
		return new Bool(this->_value >= ((Float*)other)->getValue());
	else if (other->getType() == INT)
		return new Bool(this->_value >= ((Int*)other)->getValue());
	else
		return Type::greaterEqual(other);
}

Type* Float::lessEqual(Type* other)
{
	if (other->getType() == FLOAT)
		return new Bool(this->_value <= ((Float*)other)->getValue());
	else if (other->getType() == INT)
		return new Bool(this->_value <= ((Int*)other)->getValue());
	else
		return Type::lessEqual(other);
}

Type* Float::toInt()
{
	return new Int((int)this->_value);
}

Type* Float::toBool()
{
	return new Bool((bool)this->_value);
}
