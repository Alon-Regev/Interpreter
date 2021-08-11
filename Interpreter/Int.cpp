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
	else if (other->getType() == CHAR)
		return new Char(this->_value + ((Char*)other)->getValue());
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

Type* Int::mod(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value % ((Int*)other)->_value);
	else
		Type::mod(other);
}

Type* Int::exp(Type* other)
{
	if (other->getType() == INT)
		return new Float(pow(this->_value, ((Int*)other)->_value));
	else if (other->getType() == FLOAT)
		return new Float(pow(this->_value, ((Float*)other)->getValue()));
	else
		Type::exp(other);
}

Type* Int::increment(bool post)
{
	if (!this->isVariable())
		throw InvalidOperationException("Incrementing (++) non-variable value");
	if (post)
		return new Int(this->_value++);
	else
		return new Int(++this->_value);
}

Type* Int::decrement(bool post)
{
	if (!this->isVariable())
		throw InvalidOperationException("Decrementing (++) non-variable value");
	if (post)
		return new Int(this->_value--);
	else
		return new Int(--this->_value);
}

Type* Int::bitXor(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value ^ ((Int*)other)->_value);
	else if (other->getType() == CHAR)
		return new Char(this->_value ^ ((Char*)other)->getValue());
	else
		Type::bitXor(other);
}

Type* Int::bitAnd(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value & ((Int*)other)->_value);
	else if (other->getType() == CHAR)
		return new Char(this->_value & ((Char*)other)->getValue());
	else
		Type::bitAnd(other);
}

Type* Int::bitOr(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value | ((Int*)other)->_value);
	else if (other->getType() == CHAR)
		return new Char(this->_value | ((Char*)other)->getValue());
	else
		Type::bitOr(other);
}

Type* Int::bitNot()
{
	return new Int(~this->_value);
}

Type* Int::leftShift(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value << ((Int*)other)->_value);
	else
		Type::leftShift(other);
}

Type* Int::rightShift(Type* other)
{
	if (other->getType() == INT)
		return new Int(this->_value >> ((Int*)other)->_value);
	else
		Type::rightShift(other);
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
	else if (other->getType() == CHAR)
	{
		this->_value = ((Char*)other)->getValue();
		return this;
	}
	else
		Type::assign(other);
}

Type* Int::addAssign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value += ((Int*)other)->_value;
		return this;
	}
	else if (other->getType() == FLOAT)
	{
		this->_value += ((Float*)other)->getValue();
		return this;
	}
	else
		Type::addAssign(other);
}

Type* Int::subAssign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value -= ((Int*)other)->_value;
		return this;
	}
	else if (other->getType() == FLOAT)
	{
		this->_value -= ((Float*)other)->getValue();
		return this;
	}
	else
		Type::subAssign(other);
}

Type* Int::divAssign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value /= ((Int*)other)->_value;
		return this;
	}
	else if (other->getType() == FLOAT)
	{
		this->_value /= ((Float*)other)->getValue();
		return this;
	}
	else
		Type::divAssign(other);
}

Type* Int::mulAssign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value *= ((Int*)other)->_value;
		return this;
	}
	else if (other->getType() == FLOAT)
	{
		this->_value *= ((Float*)other)->getValue();
		return this;
	}
	else
		Type::mulAssign(other);
}

Type* Int::modAssign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value %= ((Int*)other)->_value;
		return this;
	}
	else
		Type::modAssign(other);
}

Type* Int::expAssign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value = pow(this->_value, ((Int*)other)->_value);
		return this;
	}
	else if (other->getType() == FLOAT)
	{
		this->_value = pow(this->_value, ((Float*)other)->getValue());
		return this;
	}
	else
		Type::expAssign(other);
}

Type* Int::xorAssign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value ^= ((Int*)other)->_value;
		return this;
	}
	else
		Type::xorAssign(other);
}

Type* Int::andAssign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value &= ((Int*)other)->_value;
		return this;
	}
	else
		Type::andAssign(other);
}

Type* Int::orAssign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value |= ((Int*)other)->_value;
		return this;
	}
	else
		Type::orAssign(other);
}

Type* Int::leftShiftAssign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value <<= ((Int*)other)->_value;
		return this;
	}
	else
		Type::leftShiftAssign(other);
}

Type* Int::rightShiftAssign(Type* other)
{
	if (other->getType() == INT)
	{
		this->_value >>= ((Int*)other)->_value;
		return this;
	}
	else
		Type::rightShiftAssign(other);
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

Type* Int::toChar()
{
	return new Char(this->_value);
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
