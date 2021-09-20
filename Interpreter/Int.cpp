#include "Int.h"
#include "TempMemory.h"

unsigned int TempMemory<Int>::_i = 0;
Int TempMemory<Int>::_memory[MEMORY_CELLS] = { *(Int*)Int().temp(), *(Int*)Int().temp(), *(Int*)Int().temp() };

Int::Int(const std::string& value) : Type(_INT)
{
	if (Int::isType(value))
		this->_value = std::stoi(value);
	else
		throw InvalidOperationException("casting value of \"" + value + "\" to int");
}
Int::Int(const int value) : Type(_INT), _value(value) {}
Int::Int() : Type(_INT), _value(INT_DEFAULT_VALUE) {}

std::string Int::toString() const
{
	return std::to_string(this->_value);
}

Type* Int::copy()
{
	int res = this->_value;
	return TempMemory<Int>::set(&res);
}

bool Int::isType(const std::string& value)
{
	return std::regex_match(value, std::regex("\\d+"));
}

int Int::getValue()
{
	return this->_value;
}

void Int::set(void* arg)
{
	this->_value = *(int*)arg;
}

Type* Int::add(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value + ((Int*)other)->_value;
		return TempMemory<Int>::set(&res);
	}
	else if (other->getType() == _FLOAT)
	{
		double res = this->_value + ((Float*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else if (other->getType() == _CHAR)
		return new Char(this->_value + ((Char*)other)->getValue());
	else
		Type::add(other);
}

Type* Int::sub(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value - ((Int*)other)->_value;
		return TempMemory<Int>::set(&res);
	}
	else if (other->getType() == _FLOAT)
	{
		double res = this->_value - ((Float*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else
		Type::sub(other);
}

Type* Int::mul(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value * ((Int*)other)->_value;
		return TempMemory<Int>::set(&res);
	}
	else if (other->getType() == _FLOAT)
	{
		double res = this->_value * ((Float*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else
		Type::mul(other);
}

Type* Int::negative()
{
	int res = -this->_value;
	return TempMemory<Int>::set(&res);
}

Type* Int::mod(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value % ((Int*)other)->_value;
		return TempMemory<Int>::set(&res);
	}
	else
		Type::mod(other);
}

Type* Int::exp(Type* other)
{
	if (other->getType() == _INT)
	{
		double res = pow(this->_value, ((Int*)other)->_value);
		return TempMemory<Float>::set(&res);
	}
	else if (other->getType() == _FLOAT)
	{
		double res = pow(this->_value, ((Float*)other)->getValue());
		return TempMemory<Float>::set(&res);
	}
	else
		Type::exp(other);
}

Type* Int::increment(bool post)
{
	if (!this->isVariable())
		throw InvalidOperationException("Incrementing (++) non-variable value");
	if (post)
	{
		int v = this->_value++;
		return TempMemory<Int>::set(&v);
	}
	else
		return TempMemory<Int>::set(&++this->_value);
}

Type* Int::decrement(bool post)
{
	if (!this->isVariable())
		throw InvalidOperationException("Decrementing (++) non-variable value");
	if (post)
	{
		int res = this->_value--;
		return TempMemory<Int>::set(&res);
	}
	else
	{
		int res = --this->_value;
		return TempMemory<Int>::set(&res);
	}
}

Type* Int::bitXor(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value ^ ((Int*)other)->_value;
		return TempMemory<Int>::set(&res);
	}
	else if (other->getType() == _CHAR)
		return new Char(this->_value ^ ((Char*)other)->getValue());
	else
		Type::bitXor(other);
}

Type* Int::bitAnd(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value & ((Int*)other)->_value;
		return TempMemory<Int>::set(&res);
	}
	else if (other->getType() == _CHAR)
		return new Char(this->_value & ((Char*)other)->getValue());
	else
		Type::bitAnd(other);
}

Type* Int::bitOr(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value | ((Int*)other)->_value;
		return TempMemory<Int>::set(&res);
	}
	else if (other->getType() == _CHAR)
		return new Char(this->_value | ((Char*)other)->getValue());
	else
		Type::bitOr(other);
}

Type* Int::bitNot()
{
	{int res = ~this->_value;
	return TempMemory<Int>::set(&res); }
}

Type* Int::leftShift(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value << ((Int*)other)->_value;
		return TempMemory<Int>::set(&res);
	}
	else
		Type::leftShift(other);
}

Type* Int::rightShift(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value >> ((Int*)other)->_value;
		return TempMemory<Int>::set(&res);
	}
	else
		Type::rightShift(other);
}

Type* Int::assign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value = ((Int*)other)->_value;
		return this;
	}
	else if (other->getType() == _FLOAT)
	{
		this->_value = ((Float*)other)->getValue();
		return this;
	}
	else if (other->getType() == _CHAR)
	{
		this->_value = ((Char*)other)->getValue();
		return this;
	}
	else
		Type::assign(other);
}

Type* Int::addAssign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value += ((Int*)other)->_value;
		return this;
	}
	else if (other->getType() == _FLOAT)
	{
		this->_value += ((Float*)other)->getValue();
		return this;
	}
	else
		Type::addAssign(other);
}

Type* Int::subAssign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value -= ((Int*)other)->_value;
		return this;
	}
	else if (other->getType() == _FLOAT)
	{
		this->_value -= ((Float*)other)->getValue();
		return this;
	}
	else
		Type::subAssign(other);
}

Type* Int::divAssign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value /= ((Int*)other)->_value;
		return this;
	}
	else if (other->getType() == _FLOAT)
	{
		this->_value /= ((Float*)other)->getValue();
		return this;
	}
	else
		Type::divAssign(other);
}

Type* Int::mulAssign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value *= ((Int*)other)->_value;
		return this;
	}
	else if (other->getType() == _FLOAT)
	{
		this->_value *= ((Float*)other)->getValue();
		return this;
	}
	else
		Type::mulAssign(other);
}

Type* Int::modAssign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value %= ((Int*)other)->_value;
		return this;
	}
	else
		Type::modAssign(other);
}

Type* Int::expAssign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value = pow(this->_value, ((Int*)other)->_value);
		return this;
	}
	else if (other->getType() == _FLOAT)
	{
		this->_value = pow(this->_value, ((Float*)other)->getValue());
		return this;
	}
	else
		Type::expAssign(other);
}

Type* Int::xorAssign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value ^= ((Int*)other)->_value;
		return this;
	}
	else
		Type::xorAssign(other);
}

Type* Int::andAssign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value &= ((Int*)other)->_value;
		return this;
	}
	else
		Type::andAssign(other);
}

Type* Int::orAssign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value |= ((Int*)other)->_value;
		return this;
	}
	else
		Type::orAssign(other);
}

Type* Int::leftShiftAssign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value <<= ((Int*)other)->_value;
		return this;
	}
	else
		Type::leftShiftAssign(other);
}

Type* Int::rightShiftAssign(Type* other)
{
	if (other->getType() == _INT)
	{
		this->_value >>= ((Int*)other)->_value;
		return this;
	}
	else
		Type::rightShiftAssign(other);
}

Type* Int::equal(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value == ((Int*)other)->_value;
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _FLOAT)
	{
		int res = this->_value == ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		Type::equal(other);
}

Type* Int::notEqual(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value != ((Int*)other)->_value;
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _FLOAT)
	{
		int res = this->_value != ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		Type::notEqual(other);
}

Type* Int::greater(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value > ((Int*)other)->_value;
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _FLOAT)
	{
		int res = this->_value > ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		Type::greater(other);
}

Type* Int::less(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value < ((Int*)other)->_value;
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _FLOAT)
	{
		int res = this->_value < ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		Type::less(other);
}

Type* Int::greaterEqual(Type* other)
{
	if (other->getType() == _INT)
	{
		int res = this->_value >= ((Int*)other)->_value;
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _FLOAT)
	{
		int res = this->_value >= ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		Type::greaterEqual(other);
}

Type* Int::lessEqual(Type* other)
{
	if (other->getType() == _INT)
	{
		bool res = this->_value <= ((Int*)other)->_value;
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _FLOAT)
	{
		int res = this->_value <= ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		Type::lessEqual(other);
}

Type* Int::toBool()
{
	int res = (bool)this->_value;
	return TempMemory<Bool>::set(&res);
}

Type* Int::toFloat()
{
	double res = (double)this->_value;
	return TempMemory<Float>::set(&res);
}

Type* Int::toChar()
{
	return new Char(this->_value);
}

Type* Int::div(Type* other)
{
	if (other->getType() == _INT)
	{
		if (((Int*)other)->getValue() == 0)
			throw InvalidOperationException("Division by zero");
		int res = this->_value / ((Int*)other)->_value;
		return TempMemory<Int>::set(&res);
	}
	else if (other->getType() == _FLOAT)
	{
		if (((Float*)other)->getValue() == 0)
			throw InvalidOperationException("Division by zero");
		double res = this->_value / ((Float*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else
		Type::div(other);
}
