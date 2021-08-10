#include "Bool.h"

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
	return new Bool(this->_value);
}

bool Bool::isType(const std::string& value)
{
	return value == _TRUE || value == _FALSE;
}

bool Bool::getValue()
{
	return this->_value;
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
		return new Bool(this->_value == ((Bool*)other)->_value);
	else
		return Type::equal(other);
}

Type* Bool::notEqual(Type* other)
{
	if (other->getType() == _BOOL)
		return new Bool(this->_value != ((Bool*)other)->_value);
	else
		return Type::notEqual(other);
}

Type* Bool::logicOr(Type* other)
{
	if (other->getType() == _BOOL)
		return new Bool(this->_value || ((Bool*)other)->_value);
	else
		return Type::logicOr(other);
}

Type* Bool::logicAnd(Type* other)
{
	if (other->getType() == _BOOL)
		return new Bool(this->_value && ((Bool*)other)->_value);
	else
		return Type::logicAnd(other);
}

Type* Bool::toInt()
{
	return new Int((int)this->_value);
}

Type* Bool::toFloat()
{
	return new Float((double)this->_value);
}
