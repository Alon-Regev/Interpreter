#include "Bool.h"
#include "TempMemory.h"

unsigned int TempMemory<Bool>::_i = 0;
Bool TempMemory<Bool>::_memory[MEMORY_CELLS] = { *(Bool*)Bool().temp(), *(Bool*)Bool().temp(), *(Bool*)Bool().temp() };

Bool::Bool(const std::string& value) : Type(_BOOL)
{
	if (value == _FALSE)
		_value = false;
	else if (value == _TRUE)
		_value = true;
	else
		throw InvalidOperationException("casting value of \"" + value + "\" to bool");
}
Bool::Bool(bool value) : Type(_BOOL), _value(value) {}

Bool::Bool() : Type(_BOOL), _value(false) {}

std::string Bool::toString() const
{
	return this->_value ? _TRUE : _FALSE;
}

Type* Bool::copy()
{
	int res = this->_value;
	return TempMemory<Bool>::set(&res);
}

bool Bool::isType(const std::string& value)
{
	return value == _TRUE || value == _FALSE;
}

bool Bool::getValue()
{
	return this->_value;
}

void Bool::set(void* arg)
{
	this->_value = *(bool*)arg;
}

Type* Bool::assign(Type* other)
{
	if (other->getType() == _BOOL)
	{
		this->_value = ((Bool*)other)->_value;
		return this;
	}
	else
		return Type::assign(other);
}

Type* Bool::equal(Type* other)
{
	if (other->getType() == _BOOL)
	{
		int res = this->_value == ((Bool*)other)->_value;
		return TempMemory<Bool>::set(&res);
	}
	else
		return Type::equal(other);
}

Type* Bool::notEqual(Type* other)
{
	if (other->getType() == _BOOL)
	{
		int res = this->_value != ((Bool*)other)->_value;
		return TempMemory<Bool>::set(&res);
	}
	else
		return Type::notEqual(other);
}

Type* Bool::logicOr(Type* other)
{
	if (other->getType() == _BOOL)
	{
		int res = this->_value || ((Bool*)other)->_value;
		return TempMemory<Bool>::set(&res);
	}
	else
		return Type::logicOr(other);
}

Type* Bool::logicAnd(Type* other)
{
	if (other->getType() == _BOOL)
	{
		int res = this->_value && ((Bool*)other)->_value;
		return TempMemory<Bool>::set(&res);
	}
	else
		return Type::logicAnd(other);
}

Type* Bool::logicNot()
{
	{int res = !this->_value;
	return TempMemory<Bool>::set(&res); }
}

Type* Bool::ternary(Type* other)
{
	if (other->getType() == PAIR)
		return this->_value ? ((Pair*)other)->_first->tryReference() : ((Pair*)other)->_second->tryReference();
	else
		return Type::ternary(other);
}

Type* Bool::toInt()
{
	int res = (int)this->_value;
	return TempMemory<Int>::set(&res);
}

Type* Bool::toFloat()
{
	double res = (double)this->_value;
	return TempMemory<Float>::set(&res);
}
