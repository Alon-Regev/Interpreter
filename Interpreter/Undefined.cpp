#include "Undefined.h"

Undefined::Undefined() : Type(UNDEFINED)
{
}

std::string Undefined::toString() const
{
	return UNDEFINED;
}

Type* Undefined::copy()
{
	return new Undefined();
}

bool Undefined::isType(const std::string& value)
{
	return value == UNDEFINED || value == "_";
}
