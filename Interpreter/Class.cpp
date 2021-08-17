#include "Class.h"

Class::Class() : Object(CLASS)
{
}

Type* Class::assign(Type* other)
{
	if (other->getType() == OBJECT)
	{
		Object::assign(other);
		// check constructor
		if (this->_variables.find(this->_variable) != this->_variables.end())
			this->_instances.push_back(this->_variable);
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
		newCopy->toMethods();

		// call constructor and set temporary variable this
		newCopy->setVariable("this");
		delete newCopy->getVariables()[this->_variable]->call(other);
		newCopy->setVariable("");

		// delete constructors
		for (const std::string& instance : this->_instances)
		{
			if (this->_variables.find(instance) != this->_variables.end())
			{
				delete newCopy->getVariables()[instance];
				newCopy->getVariables().erase(instance);
			}
		}
		return newCopy;
	}
	else
		throw SyntaxException("Constructing static class (with no constructor)");
}
