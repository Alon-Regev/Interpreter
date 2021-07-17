#include "Function.h"

Function::Function(Interpreter& interpreter) : Type(FUNCTION), _interpreter(interpreter) {}

Function::Function(Type* params, Block* block) : Type(FUNCTION), _interpreter(block->getInterpreter()), _function(block->copy())
{
	if (params->getType() == TUPLE && ((Tuple*)params)->isVariableTuple())
	{	// multiple params
		for (Type* param : ((Tuple*)params)->getValues())
		{
			this->_parameters.push_back(Parameter{ param->getVariable(), param->getType() });
			Interpreter::removeVariable(param->getVariable());
		}
		((Tuple*)params)->getValues().clear();
		delete params;
	}
	else if (params->getType() != UNDEFINED && params->isVariable())
	{	// one param
		this->_parameters.push_back(Parameter{ params->getVariable(), params->getType() });
		Interpreter::removeVariable(params->getVariable());
	}
}

Function::~Function()
{
	delete this->_function;
}

Type* Function::call(Type* other)
{
	if (this->_parameters.empty() && other->getType() != UNDEFINED)
		throw InvalidOperationException("arguments to a function with no parameters");

	Interpreter::openScope();
	if (this->_parameters.size() == 1)
		Interpreter::addVariable(this->_parameters[0].name, other, false, true);
	else if(this->_parameters.size() != 0)
	{
		for (int i = 0; i < this->_parameters.size(); i++)
			Interpreter::addVariable(this->_parameters[i].name, ((Tuple*)other)->getValues()[i], false, true);
		((Tuple*)other)->getValues().clear();
	}

	Type* ret = nullptr;
	if (this->_function->getType() != BLOCK)
		ret = this->_function->copy();
	else
		ret = ((Block*)this->_function)->run();
	Interpreter::closeScope();
	return ret;
}

Type* Function::assign(Type* other)
{
	if (other->getType() == FUNCTION)
	{
		this->_function = ((Function*)other)->_function->copy();
		this->_parameters = ((Function*)other)->_parameters;
		return this;
	}
	else
		return Type::assign(other);
}
