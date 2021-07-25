#include "Class.h"

Class::Class() : Object(CLASS)
{
}

Type* Class::assign(Type* other)
{
	if (other->getType() == OBJECT)
	{
		Object::assign(other);
		return this;
	}
	else
		return Type::assign(other);
}

Type* Class::call(Type* other)
{
	// call constructor
	if (this->_variables.find(this->_variable) != this->_variables.end())
	{
		Object* newCopy = (Object*)this->copy();
		//newCopy->toMethods();
		delete newCopy->_variables[this->_variable]->call(nullptr);
		delete newCopy->_variables[this->_variable];
		newCopy->_variables.erase(this->_variable);
		return newCopy;
	}
	else
		throw SyntaxException("Constructing class with no constructor");
}
