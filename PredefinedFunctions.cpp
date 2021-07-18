#include "PredefinedFunctions.h"

void initVariables(std::map<std::string, Type*>& variables)
{
	setVariable("print", new StaticFunction(print), variables);
	setVariable("delete", new StaticFunction(deleteVariable), variables);
}

void setVariable(const std::string& name, Type* type, std::map<std::string, Type*>& variables)
{
	variables[name] = type;
	variables[name]->setVariable(name);
}

Type* print(Type* other)
{
	if (other->getType() == TUPLE)
	{
		std::string result = "";
		for (const Type* type : *((Tuple*)other))
		{
			result += type->toString() + " ";
		}
		result.pop_back();
		std::cout << result << std::endl;
	}
	else
	{
		std::cout << other->toString() << std::endl;
	}
	return new Void();
}

Type* deleteVariable(Type* type)
{
	if (type->isVariable())
	{
		Interpreter::removeVariable(type->getVariable());
	}
	else
		throw InvalidOperationException("Deleting a non-variable value");
	return new Void();
}