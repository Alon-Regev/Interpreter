#include "PredefinedFunctions.h"

void initVariables(std::map<std::string, Type*>& variables)
{
	variables["print"] = new StaticFunction(print);
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