#include "Reference.h"

Reference::Reference() : Type(REFERENCE), _value(nullptr)
{
}

Reference::Reference(Type* other) : Type(REFERENCE), _value(other)
{
}

std::string Reference::toString() const
{
	this->checkReference();
	return this->_value->toString();
}

Type* Reference::copy()
{
	return new Reference(this->_value);
}

Type* Reference::getValue()
{
	return _value;
}

Type* Reference::add(Type* other)
{
	this->checkReference();
	return this->_value->add(other);
}

Type* Reference::sub(Type* other)
{
	this->checkReference();
	return this->_value->sub(other);
}

Type* Reference::div(Type* other)
{
	this->checkReference();
	return this->_value->div(other);
}

Type* Reference::mul(Type* other)
{
	this->checkReference();
	return this->_value->mul(other);
}

Type* Reference::assign(Type* other)
{
	if (this->_value == nullptr)
		this->_value = other;
	else
	{
		this->_value->assign(other);
		return this;
	}
}

Type* Reference::call(Type* other)
{
	this->checkReference();
	return this->_value->call(other);
}

Type* Reference::block(Type* other)
{
	this->checkReference();
	return this->_value->block(other);
}

Type* Reference::index(Type* other)
{
	this->checkReference();
	return this->_value->index(other);
}

Type* Reference::point(Type* other)
{
	this->checkReference();
	return this->_value->point(other);
}

Type* Reference::negative()
{
	this->checkReference();
	return this->_value->negative();
}

Type* Reference::equal(Type* other)
{
	this->checkReference();
	return this->_value->equal(other);
}

Type* Reference::notEqual(Type* other)
{
	this->checkReference();
	return this->_value->notEqual(other);
}

Type* Reference::greater(Type* other)
{
	this->checkReference();
	return this->_value->greater(other);
}

Type* Reference::less(Type* other)
{
	this->checkReference();
	return this->_value->less(other);
}

Type* Reference::greaterEqual(Type* other)
{
	this->checkReference();
	return this->_value->greaterEqual(other);
}

Type* Reference::lessEqual(Type* other)
{
	this->checkReference();
	return this->_value->lessEqual(other);
}

Type* Reference::logicOr(Type* other)
{
	this->checkReference();
	return this->_value->logicOr(other);
}

Type* Reference::logicAnd(Type* other)
{
	this->checkReference();
	return this->_value->logicAnd(other);
}

void Reference::checkReference() const
{
	if (this->_value == nullptr)
		throw VariableException("Empty reference");
}
