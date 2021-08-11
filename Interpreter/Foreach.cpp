#include "Foreach.h"

Foreach::Foreach(Type* parameters) : Type(FOREACH)
{
	if (parameters->getType() == TUPLE && ((Tuple*)parameters)->getValues().size() == 2 && ((Tuple*)parameters)->getValues()[0]->isVariable())
	{
		std::string containerType = ((Tuple*)parameters)->getValues()[1]->getType();
		if (containerType == LIST || containerType == STRING || containerType == TUPLE)
		{
			this->_current = ((Tuple*)parameters)->getValues()[0];
			this->_container = ((Tuple*)parameters)->getValues()[1];
			return;
		}
	}
	throw SyntaxException("Invalid foreach parameters");
}

Type* Foreach::block(Type* other)
{
	if (other->getType() != BLOCK)
		throw SyntaxException("Invalid foreach syntax");
	if (this->_container->getType() == LIST)
	{
		for (Type* value : ((List*)this->_container)->getContent())
		{
			Interpreter::assign(this->_current, value);
			((Block*)other)->run();
		}
	}
	else if (this->_container->getType() == STRING)
	{
		for (char value : ((String*)this->_container)->getContent())
		{
			this->_current->assign(new String(std::string{ value }));
			((Block*)other)->run();
		}
	}
	else if (this->_container->getType() == TUPLE)
	{
		for (Type* value : *((Tuple*)this->_container))
		{
			this->_current->assign(value);
			((Block*)other)->run();
		}
	}
	return new Undefined();
}
