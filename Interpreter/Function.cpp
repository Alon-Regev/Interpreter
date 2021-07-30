#include "Function.h"

Function::Function(Interpreter& interpreter) : Type(FUNCTION), _interpreter(interpreter), _function(nullptr)  {}

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
	else if (params->isVariable())
	{	// one param
		this->_parameters.push_back(Parameter{ params->getVariable(), (params->isStaticType() ? params->getType() : "") });
		Interpreter::removeVariable(params->getVariable());
	}
	else
	{
		// zero params
		delete params;
	}
}

Function::Function(std::vector<Parameter>& parameters, Type* function, Interpreter& interpreter, Type* thisType) : Type(FUNCTION), _parameters(parameters), _function(function->copy()), _interpreter(interpreter), _this(thisType ? thisType->copy() : nullptr)
{
}

Function::~Function()
{
	delete this->_function;
	delete this->_this;
}

Type* Function::copy()
{
	return new Function(this->_parameters, this->_function, this->_interpreter, this->_this);
}

void Function::setThis(Type* value, bool deletePrev)
{
	//if(deletePrev)
		delete this->_this;
	this->_this = value;
}

Type* Function::call(Type* other)
{
	if (other)
	{
		if (this->_parameters.empty() && other->getType() != UNDEFINED)
			throw InvalidOperationException("arguments to a function with no parameters");

		Interpreter::openScope();
		if (this->_parameters.size() == 1)
		{
			Interpreter::addVariable(this->_parameters[0].name, this->_parameters[0].type == REFERENCE ? new Reference(other) : other, false, true);
		}
		else if (this->_parameters.size() != 0)
		{
			// other doesn't have multiple arguments
			if (other->getType() != TUPLE || ((Tuple*)other)->getValues().size() != this->_parameters.size())
				throw InvalidOperationException("Invalid argument count");
			for (int i = 0; i < this->_parameters.size(); i++)
			{
				Type* value = ((Tuple*)other)->getValues()[i];
				Interpreter::addVariable(this->_parameters[i].name, this->_parameters[i].type == REFERENCE ? new Reference(value) : value, false, true);
			}
			((Tuple*)other)->getValues().clear();
		}
	}
	else
		Interpreter::openScope();
	if (this->_this)
		Interpreter::addVariable("this", new Reference(this->_this), false, true);

	Type* ret = nullptr;
	if (this->_function->getType() != BLOCK)
		ret = this->_function->copy();
	else
		ret = ((Block*)this->_function)->run(false);
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
