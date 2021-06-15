#include "Function.h"

Function::Function(Interpreter& interpreter) : Type(FUNCTION), _interpreter(interpreter) {}

Function::Function(Type* params, Block* block) : Type(FUNCTION), _interpreter(block->getInterpreter()), _function(block) 
{
	if (params->getType() == UNDEFINED || params->getType() == TUPLE && ((Tuple*)params)->isVariableTuple() || params->isVariable())
		this->_params = params;
}

Type* Function::call(Type* other)
{
	if (this->_params->getType() == UNDEFINED && other->getType() != UNDEFINED)
		throw InvalidOperationException("arguments to a function with no parameters");
	else if(!(this->_params->getType() == UNDEFINED && other->getType() == UNDEFINED))
		this->_params->assign(other);
	if (this->_function->getType() != BLOCK)
		return this->_function->copy();
	else
		return ((Block*)this->_function)->run();
}

Type* Function::assign(Type* other)
{
	if (other->getType() == FUNCTION)
	{
		this->_function = ((Function*)other)->_function;
		this->_params = ((Function*)other)->_params;
	}
	else
		return Type::assign(other);
}
