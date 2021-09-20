#include "Float.h"
#include "TempMemory.h"

unsigned int TempMemory<Float>::_i = 0;
Float TempMemory<Float>::_memory[MEMORY_CELLS] = { *(Float*)Float().temp(), *(Float*)Float().temp(), *(Float*)Float().temp() };

Float::Float(const std::string& value) : Type(_FLOAT)
{
	if (Float::isType(value))
		this->_value = std::stod(value);
	else
		throw InvalidOperationException("casting value of \"" + value + "\" to float");
}

Float::Float(const double value) : Type(_FLOAT), _value(value)
{
}

Float::Float() : Type(_FLOAT), _value(0)
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
	double res = this->_value;
	return TempMemory<Float>::set(&res);
}

bool Float::isType(const std::string& value)
{
	return std::regex_match(value, std::regex(R"((?=[\d\.]*?\d)\d*\.?\d*(e-?\d+)?)"));
}

double Float::getValue()
{
	return this->_value;
}

void Float::set(void* arg)
{
	this->_value = *(double*)arg;
}

Type* Float::add(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		double res = this->_value + ((Float*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else if (other->getType() == _INT)
	{
		double res = this->_value + ((Int*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else
		return Type::add(other);
}

Type* Float::sub(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		double res = this->_value - ((Float*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else if (other->getType() == _INT)
	{
		double res = this->_value - ((Int*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else
		return Type::sub(other);
}

Type* Float::div(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		if (((Float*)other)->getValue() == 0)
			throw InvalidOperationException("Division by zero");
		double res = this->_value / ((Float*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else if (other->getType() == _INT)
	{
		if (((Int*)other)->getValue() == 0)
			throw InvalidOperationException("Division by zero");
		double res = this->_value / ((Int*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else
		return Type::div(other);
}

Type* Float::mul(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		double res = this->_value * ((Float*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else if (other->getType() == _INT)
	{
		double res = this->_value * ((Int*)other)->getValue();
		return TempMemory<Float>::set(&res);
	}
	else
		return Type::mul(other);
}

Type* Float::exp(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		double res = pow(this->_value, ((Float*)other)->getValue());
		return TempMemory<Float>::set(&res);
	}
	else if (other->getType() == _INT)
	{
		double res = pow(this->_value, ((Int*)other)->getValue());
		return TempMemory<Float>::set(&res);
	}
	else
		return Type::exp(other);
}

Type* Float::negative()
{
	double res = -this->_value;
	return TempMemory<Float>::set(&res);
}

Type* Float::assign(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		this->_value = ((Float*)other)->getValue();
		return this;
	}
	else if (other->getType() == _INT)
	{
		this->_value = ((Int*)other)->getValue();
		return this;
	}
	else
		Type::assign(other);
}

Type* Float::addAssign(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		this->_value += ((Float*)other)->getValue();
		return this;
	}
	else if (other->getType() == _INT)
	{
		this->_value += ((Int*)other)->getValue();
		return this;
	}
	else
		Type::addAssign(other);
}

Type* Float::subAssign(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		this->_value -= ((Float*)other)->getValue();
		return this;
	}
	else if (other->getType() == _INT)
	{
		this->_value -= ((Int*)other)->getValue();
		return this;
	}
	else
		Type::subAssign(other);
}

Type* Float::divAssign(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		this->_value /= ((Float*)other)->getValue();
		return this;
	}
	else if (other->getType() == _INT)
	{
		this->_value /= ((Int*)other)->getValue();
		return this;
	}
	else
		Type::divAssign(other);
}

Type* Float::mulAssign(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		this->_value *= ((Float*)other)->getValue();
		return this;
	}
	else if (other->getType() == _INT)
	{
		this->_value *= ((Int*)other)->getValue();
		return this;
	}
	else
		Type::mulAssign(other);
}

Type* Float::expAssign(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		this->_value = pow(this->_value, ((Float*)other)->getValue());
		return this;
	}
	else if (other->getType() == _INT)
	{
		this->_value = pow(this->_value, ((Int*)other)->getValue());
		return this;
	}
	else
		Type::expAssign(other);
}

Type* Float::equal(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		int res = this->_value == ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _INT)
	{
		int res = this->_value == ((Int*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		return Type::equal(other);
}

Type* Float::notEqual(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		int res = this->_value != ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _INT)
	{
		int res = this->_value != ((Int*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		return Type::notEqual(other);
}

Type* Float::greater(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		int res = this->_value > ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _INT)
	{
		int res = this->_value > ((Int*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		return Type::greater(other);
}

Type* Float::less(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		int res = this->_value < ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _INT)
	{
		int res = this->_value < ((Int*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		return Type::less(other);
}

Type* Float::greaterEqual(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		int res = this->_value >= ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _INT)
	{
		int res = this->_value >= ((Int*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		return Type::greaterEqual(other);
}

Type* Float::lessEqual(Type* other)
{
	if (other->getType() == _FLOAT)
	{
		int res = this->_value <= ((Float*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else if (other->getType() == _INT)
	{
		int res = this->_value <= ((Int*)other)->getValue();
		return TempMemory<Bool>::set(&res);
	}
	else
		return Type::lessEqual(other);
}

Type* Float::toInt()
{
	int res = (int)this->_value;
	return TempMemory<Int>::set(&res);
}

Type* Float::toBool()
{
	int res = (bool)this->_value;
	return TempMemory<Bool>::set(&res);
}
