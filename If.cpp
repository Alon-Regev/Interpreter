#include "If.h"

If::If(Type* condition) : Type(IF)
{
	if (condition->getType() == BOOL)
		this->_condition = ((Bool*)condition)->getValue();
}

Type* If::block(Type* other)
{
	if (other->getType() != BLOCK)
		return Type::block(other);
	// run if condition is true
	if (_condition)
		return ((Block*)other)->run();
	else
		return new Undefined();		// maybe return else statement?
}
