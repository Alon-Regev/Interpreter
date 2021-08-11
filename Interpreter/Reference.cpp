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

Type* Reference::mod(Type* other)
{
	this->checkReference();
	return this->_value->mod(other);
}

Type* Reference::exp(Type* other)
{
	this->checkReference();
	return this->_value->exp(other);
}

Type* Reference::increment(bool post)
{
	this->checkReference();
	return this->_value->increment(post);
}

Type* Reference::decrement(bool post)
{
	this->checkReference();
	return this->_value->decrement(post);
}

Type* Reference::bitXor(Type* other)
{
	this->checkReference();
	return this->_value->bitXor(other);
}

Type* Reference::bitAnd(Type* other)
{
	this->checkReference();
	return this->_value->bitAnd(other);
}

Type* Reference::bitOr(Type* other)
{
	this->checkReference();
	return this->_value->bitOr(other);
}

Type* Reference::bitNot()
{
	this->checkReference();
	return this->_value->bitNot();
}

Type* Reference::leftShift(Type* other)
{
	this->checkReference();
	return this->_value->leftShift(other);
}

Type* Reference::rightShift(Type* other)
{
	this->checkReference();
	return this->_value->rightShift(other);
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

Type* Reference::addAssign(Type* other)
{
	this->checkReference();
	this->_value->addAssign(other);
	return this;
}

Type* Reference::subAssign(Type* other)
{
	this->checkReference();
	this->_value->subAssign(other);
	return this;
}

Type* Reference::divAssign(Type* other)
{
	this->checkReference();
	this->_value->divAssign(other);
	return this;
}

Type* Reference::mulAssign(Type* other)
{
	this->checkReference();
	this->_value->mulAssign(other);
	return this;
}

Type* Reference::modAssign(Type* other)
{
	this->checkReference();
	this->_value->modAssign(other);
	return this;
}

Type* Reference::expAssign(Type* other)
{
	this->checkReference();
	this->_value->expAssign(other);
	return this;
}

Type* Reference::xorAssign(Type* other)
{
	this->checkReference();
	this->_value->xorAssign(other);
	return this;
}

Type* Reference::andAssign(Type* other)
{
	this->checkReference();
	this->_value->andAssign(other);
	return this;
}

Type* Reference::orAssign(Type* other)
{
	this->checkReference();
	this->_value->orAssign(other);
	return this;
}

Type* Reference::leftShiftAssign(Type* other)
{
	this->checkReference();
	this->_value->leftShiftAssign(other);
	return this;
}

Type* Reference::rightShiftAssign(Type* other)
{
	this->checkReference();
	this->_value->rightShiftAssign(other);
	return this;
}

Type* Reference::extendAssign(Type* other)
{
	this->checkReference();
	this->_value->extendAssign(other);
	return this;
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

Type* Reference::extend(Type* other)
{
	this->checkReference();
	return this->_value->extend(other);
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

Type* Reference::logicNot()
{
	this->checkReference();
	return this->_value->logicNot();
}

Type* Reference::toInt()
{
	this->checkReference();
	return this->_value->toInt();
}

Type* Reference::toBool()
{
	this->checkReference();
	return this->_value->toBool();
}

Type* Reference::toFloat()
{
	this->checkReference();
	return this->_value->toFloat();
}

Type* Reference::toChar()
{
	this->checkReference();
	return this->_value->toChar();
}

void Reference::checkReference() const
{
	if (this->_value == nullptr)
		throw VariableException("Empty reference");
}
