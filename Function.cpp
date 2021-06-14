#include "Function.h"

Function::Function(Interpreter& interpreter) : Type(FUNCTION), _interpreter(interpreter) {}

Function::Function(Type* params, Block* block) : Type(FUNCTION), _interpreter(block->getInterpreter()), _function(block) 
{
	if (params->getType() == UNDEFINED)
		this->_params = nullptr;
	else if(params->getType() == TUPLE)
		this->_params = (Tuple*)params;
}

Type* Function::call(Type* other)
{
	this->_params->assign(other);
	return this->_function->run();
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
