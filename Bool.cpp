#include "Bool.h"

Bool::Bool(const std::string& value) : Type(BOOL)
{
	if (value == FALSE)
		_value = false;
	else if (value == TRUE)
		_value = true;
}
Bool::Bool(bool value) : Type(BOOL), _value(value) {}

Bool::Bool() : Type(BOOL), _value(false) {}

std::string Bool::toString() const
{
	return this->_value ? TRUE : FALSE;
}

Type* Bool::copy()
{
	return nullptr;
}

bool Bool::isType(const std::string& value)
{
	return value == TRUE || value == FALSE;
}

bool Bool::getValue()
{
	return this->_value;
}

Type* Bool::assign(Type* other)
{
	if (other->getType() == BOOL)
	{
		this->_value = ((Bool*)other)->_value;
		return this;
	}
	else
		return Type::assign(other);
}

Type* Bool::equal(Type* other)
{
	if (other->getType() == BOOL)
		return new Bool(this->_value == ((Bool*)other)->_value);
	else
		return Type::equal(other);
}

Type* Bool::notEqual(Type* other)
{
	if (other->getType() == BOOL)
		return new Bool(this->_value != ((Bool*)other)->_value);
	else
		return Type::notEqual(other);
}

Type* Bool::logicOr(Type* other)
{
	if (other->getType() == BOOL)
		return new Bool(this->_value || ((Bool*)other)->_value);
	else
		return Type::logicOr(other);
}

Type* Bool::logicAnd(Type* other)
{
	if (other->getType() == BOOL)
		return new Bool(this->_value && ((Bool*)other)->_value);
	else
		return Type::logicAnd(other);
}
