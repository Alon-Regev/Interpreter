#include "Function.h"

Function::Function(Interpreter& interpreter) : Type(FUNCTION), _interpreter(interpreter), _functionInstances{}  {}

Function::Function(Type* params, Block* block, std::map<std::string, Type*>& variables) : Type(FUNCTION), _interpreter(block->getInterpreter()), _functionInstances{}
{
	std::vector<Parameter> parameters;
	if (params->getType() == TUPLE && ((Tuple*)params)->isVariableTuple())
	{	// multiple params
		for (Type* param : ((Tuple*)params)->getValues())
		{
			parameters.push_back(Parameter{ param->getVariable(), param->getType() });
			Interpreter::removeVariable(param->getVariable(), block->getVariables());
		}
		((Tuple*)params)->getValues().clear();
	}
	else if (params->isVariable())
	{	// one param
		parameters.push_back(Parameter{ params->getVariable(), (params->isStaticType() ? params->getType() : ANY) });
		std::string name = params->getVariable();
		// delete variable at parent and at the block
		Interpreter::removeVariable(name, block->getVariables(), false);
		Interpreter::removeVariable(name, variables, false);
	}

	this->_functionInstances.push_back(FunctionInstance{ parameters, (Block*)block->copy() });
}

Function::Function(std::vector<FunctionInstance>& functionInstances, Interpreter& interpreter, Type* thisType) : Type(FUNCTION), _functionInstances{}, _interpreter(interpreter), _this(thisType ? thisType->copy() : nullptr)
{
	for (FunctionInstance& functionInstance : functionInstances)
		this->_functionInstances.push_back({ functionInstance.parameters, (Block*)functionInstance.function->copy() });
}

Function::~Function()
{
	for (FunctionInstance& functionInstance : this->_functionInstances)
		delete functionInstance.function;
	delete this->_this;
}

Type* Function::copy()
{
	return new Function(this->_functionInstances, this->_interpreter, this->_this);
}

void Function::setThis(Type* value, bool deletePrev)
{
	//if(deletePrev)
	delete this->_this;
	this->_this = value;
}

Type* Function::call(Type* other)
{
	// get other to vector
	std::vector<Type*> args;
	if (other->getType() != UNDEFINED && other->getType() != _VOID)
	{
		if (other->getType() == TUPLE)
			args.assign(((Tuple*)other)->getValues().begin(), ((Tuple*)other)->getValues().end());
		else
			args.push_back(other);
	}
	// choose fitting function instance
	FunctionInstance* fittingFunctionInstance = nullptr;
	for (FunctionInstance& functionInstance : this->_functionInstances)
	{
		// check arg count
		if (args.size() != functionInstance.parameters.size())
			continue;
		// check arg types
		bool stopped = false;
		for (int i = 0; i < args.size() && !stopped; i++)
		{
			// check if type doesn't fit
			if (args[i]->getType() != functionInstance.parameters[i].type && functionInstance.parameters[i].type != ANY && functionInstance.parameters[i].type != REFERENCE)
				stopped = true;
		}
		if (!stopped)
		{
			fittingFunctionInstance = &functionInstance;
			break;
		}
	}
	if (fittingFunctionInstance == nullptr)
		throw SyntaxException("Arguments don't fit any of the overloaded functions");
	return this->run(*fittingFunctionInstance, args);
}

Type* Function::assign(Type* other)
{
	if (other->getType() == FUNCTION)
	{
		// delete current function instances
		for (FunctionInstance& functionInstance : this->_functionInstances)
			delete functionInstance.function;
		this->_functionInstances.clear();
		// copy new function instances
		for (FunctionInstance& functionInstance : ((Function*)other)->_functionInstances)
			this->_functionInstances.push_back({ functionInstance.parameters, (Block*)functionInstance.function->copy() });
		return this;
	}
	else
		return Type::assign(other);
}

Type* Function::extend(Type* other)
{
	if (other->getType() != FUNCTION)
		return Type::extendAssign(other);
	return this->copy()->extendAssign(other);
}

Type* Function::extendAssign(Type* other)
{
	if (other->getType() != FUNCTION)
		return Type::extendAssign(other);
	for(FunctionInstance& functionInstance : ((Function*)other)->_functionInstances)
		this->_functionInstances.push_back({ functionInstance.parameters, (Block*)functionInstance.function->copy() });
	return this;
}

Type* Function::run(FunctionInstance& function, std::vector<Type*>& args)
{
	// add temporary paramter variables
	for (int i = 0; i < args.size(); i++)
	{
		Interpreter::addVariable(function.parameters[i].name, function.function->getVariables(), function.parameters[i].type == REFERENCE ? new Reference(args[i]) : args[i]->copy(), false, true);
	}
	if (this->_this)
		Interpreter::addVariable("this", function.function->getVariables(),new Reference(this->_this), false, true);
	// run and close scope
	Type* ret = nullptr;
	if (function.function->getType() == BLOCK)
	{
		try
		{
			ret = function.function->run();
		}
		catch (ReturnException& e)
		{
			ret = e.getValue();
		}
	}
	else
		ret = new Undefined();
	return ret;
}
