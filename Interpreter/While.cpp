#include "While.h"

While::While(Type* condition) : Type(WHILE), _condition(condition->copy())
{	
}

While::~While()
{
	delete this->_condition;
}

Type* While::block(Type* other)
{
	if (other->getType() != BLOCK)
		throw InvalidOperationException("invalid while loop");
	while (this->getCondition())
	{
		Type* res = ((Block*)other)->run();
		if(!res->isVariable())
			delete res;
	}
	return new Undefined();
}

bool While::getCondition()
{
	if (this->_condition->getType() == _BOOL)
		return ((Bool*)this->_condition)->getValue();
	else if (this->_condition->getType() == BLOCK)
	{
		Type* res = ((Block*)this->_condition)->run();
		bool ret = false;
		if (res->getType() == _BOOL)
			ret = ((Bool*)res)->getValue();
		if (!res->isVariable())
			delete res;
		return ret;
	}
}
