#include "Name.h"

Name::Name(const std::string& str) : Type(NAME), _name(str)
{
}

std::string Name::toString() const
{
	return typeNames[UNDEFINED];
}

Type* Name::copy()
{
	return new Name(this->_name);
}
