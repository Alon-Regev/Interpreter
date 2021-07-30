#include "If.h"

If::If(Type* condition) : Type(IF)
{
	if (condition->getType() == _BOOL)
		this->_condition = ((Bool*)condition)->getValue();
}

Type* If::block(Type* other)
{
	// run or return if condition is true
	if (_condition)
	{
		if (other->getType() == BLOCK)
			return ((Block*)other)->run();
		else
			return other;
	}
	else
		return new Signal(ELSE_SIGNAL);
}

Type* If::elseCheck(Type* ifReturn, Type* other)
{
	if (ifReturn->getType() == SIGNAL && ((Signal*)ifReturn)->getValue() == ELSE_SIGNAL)
	{
		// activate else
		if (other->getType() == BLOCK)
		{
			return ((Block*)other)->run();
		}
		else
			return other;
	}
	return ifReturn;
}
