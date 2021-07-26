#include "Pair.h"

Pair::Pair(Type* a, Type* b) : Type(PAIR), _first(a), _second(b)
{
}

Pair::~Pair()
{
	if (!this->_first->isVariable())
		delete this->_first;
	if (!this->_second->isVariable())
		delete this->_second;
}

std::string Pair::toString() const
{
	return this->_first->toString() + ": " + this->_second->toString();
}

Type* Pair::copy()
{
	return new Pair(this->_first->copy(), this->_second->copy());
}
