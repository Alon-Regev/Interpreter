#include "While.h"

While::While(Type* condition) : Type(WHILE), _condition(condition)
{	
}

Type* While::block(Type* other)
{
	if (other->getType() != BLOCK)
		throw InvalidOperationException("invalid while loop");
	while (this->getCondition())
		((Block*)other)->run();
	return new Undefined();
}

bool While::getCondition()
{
	if (this->_condition->getType() == BOOL)
		return ((Bool*)this->_condition)->getValue();
	else if (this->_condition->getType() == BLOCK)
	{
		Type* res = ((Block*)this->_condition)->run();
		if (res->getType() == BOOL)
			return ((Bool*)res)->getValue();
	}
	return false;
}
