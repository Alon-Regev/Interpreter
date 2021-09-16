#include "PredefinedFunctions.h"

void initVariables(std::map<std::string, Type*>& variables)
{
	setVariable("print", new StaticFunction(print), variables);
	setVariable("input", new StaticFunction(input), variables);
	setVariable("delete", new StaticFunction(deleteVariable), variables);
	setVariable("typeof", new StaticFunction(typeof), variables);
	setVariable("instanceof", new StaticFunction(instanceof), variables);
	setVariable("random", new StaticFunction(random), variables);
	setVariable("range", new StaticFunction(range), variables);
	setVariable("length", new StaticFunction(length), variables);

	setVariable("find", new StaticFunction(find), variables);
	setVariable("sort", new StaticFunction(sort), variables);

	setVariable("lower", new StaticFunction(lower), variables);
	setVariable("upper", new StaticFunction(upper), variables);

	setVariable("return", new StaticFunction(ret), variables);
	setVariable("throw", new StaticFunction(throwFunc), variables);

	setVariable("sleep", new StaticFunction(sleep), variables);
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

Type* input(Type* other)
{
	if (other->getType() != UNDEFINED)
		std::cout << other->toString();
	std::string userInput;
	std::getline(std::cin, userInput);
	return new String(userInput);
}

Type* deleteVariable(Type* type)
{
	if (type->isVariable())
	{
		//Interpreter::removeVariable(type->getVariable());
	}
	else
		throw InvalidOperationException("Deleting a non-variable value");
	return new Void();
}

Type* typeof(Type* other)
{
	return new String(typeNames[other->getType()]);
}

Type* instanceof(Type* other)
{
	if (other->getType() != TUPLE || ((Tuple*)other)->getValues().size() != 2)
		throw SyntaxException("instanceof expects two arguments");
	// get 2 args
	std::vector<Type*>& args = ((Tuple*)other)->getValues();
	if (args[1]->getType() != STRING)
		throw SyntaxException("instanceof second argument should be a string of the instance name");

	if (args[0]->getType() != OBJECT && args[0]->getType() != CLASS)
		// check type
		return new Bool(typeNames[args[0]->getType()] == args[1]->toString());
	else
	{	// check instance
		std::vector<std::string>& instances = ((Object*)args[0])->getInstances();
		std::string toFind = ((String*)args[1])->toString();
		// try to find in vector
		for (std::string& instance : instances)
		{
			if (instance == toFind)
				return new Bool(true);
		}
		// not found
		return new Bool(false);
	}
}

Type* length(Type* other)
{
	if (other->getType() == LIST)
		return new Int(((List*)other)->getContent().size());
	else if (other->getType() == TUPLE)
		return new Int(((Tuple*)other)->getValues().size());
	else if (other->getType() == STRING)
		return new Int(((String*)other)->getContent().size());
	else if (other->getType() == OBJECT)
		return new Int(((Object*)other)->getVariables().size());
	else
		throw InvalidOperationException("Can't get length of type \"" + std::string(typeNames[other->getType()]) + "\"");
}

Type* random(Type* other)
{
	if (other->getType() == _INT)
	{
		if (((Int*)other)->getValue() > RAND_MAX)
			throw InvalidOperationException("Can't produce random numbers in a range larger than " + std::to_string(RAND_MAX));
		return new Int(rand() % ((Int*)other)->getValue());
	}
	else if (other->getType() == TUPLE)
	{
		std::vector<Type*>& args = ((Tuple*)other)->getValues();
		// check arguments
		if(args.size() != 2)
			throw SyntaxException("Random function can only get 1 or 2 arguments");
		if(args[0]->getType() != _INT || args[1]->getType() != _INT)
			throw SyntaxException("Random function only gets int arguments");
		if(((Int*)args[0])->getValue() >= ((Int*)args[1])->getValue())
			throw InvalidOperationException("Random function got min value bigger of equal to max");
		// return random between the arguments
		if((((Int*)args[1])->getValue() - ((Int*)args[0])->getValue() + 1) > RAND_MAX)\
			throw InvalidOperationException("Can't produce random numbers in a range larger than " + std::to_string(RAND_MAX));
		return new Int(rand() % (((Int*)args[1])->getValue() - ((Int*)args[0])->getValue() + 1) + ((Int*)args[0])->getValue());
	}
	else
		throw SyntaxException("Invalid use of the random function");
}

Type* range(Type* other)
{
	std::vector<int> args;
	if (other->getType() == _INT)
	{
		args.push_back(0);
		args.push_back(((Int*)other)->getValue());
		args.push_back(1);
	}
	else if (other->getType() == TUPLE && (other))
	{
		for (Type* type : ((Tuple*)other)->getValues())
		{
			if (type->getType() != _INT)
				throw InvalidOperationException("Range function only gets ints");
			args.push_back(((Int*)type)->getValue());
		}
		if (args.size() == 2)
			args.push_back(1);
	}
	else
		throw InvalidOperationException("Range function invalid arguments");
	List* result = new List();
	for (int i = args[0]; args[2] > 0 ? i < args[1] : i > args[1]; i += args[2])
		result->push(new Int(i));
	return result;
}

Type* find(Type* other)
{
	if (other->getType() != TUPLE || ((Tuple*)other)->getValues().size() != 2)
		throw SyntaxException("find should get two arguments");
	Type* toFind = ((Tuple*)other)->getValues()[0];
	Type* findIn = ((Tuple*)other)->getValues()[1];
	if (findIn->getType() == STRING)
	{
		if (toFind->getType() == _CHAR)
			return new Bool(((String*)findIn)->getContent().find(((Char*)toFind)->getValue()) != std::string::npos);
		else if (toFind->getType() == STRING)
			return new Bool(((String*)findIn)->getContent().find(((String*)toFind)->getContent()) != std::string::npos);
		else
			throw SyntaxException("Can only search char or string in string");
	}
	else if (findIn->getType() == LIST)
	{
		for (Type* type : ((List*)findIn)->getContent())
		{
			Type* ret = toFind->equal(type);
			if (ret->getType() == _BOOL && ((Bool*)ret)->getValue())
				return ret;	// found
			else
				delete ret;	// not found
		}
		return new Bool(false);
	}
	else if (findIn->getType() == OBJECT)
		return new Bool(((Object*)findIn)->getVariables().find(toFind->toString()) != ((Object*)findIn)->getVariables().end());
	else
		throw SyntaxException("Can't search in type \"" + std::string(typeNames[findIn->getType()]) + "\"");
}

bool compare(Type* a, Type* b)
{
	Type* ret = a->less(b);
	bool result = false;
	if (ret->getType() != _BOOL)
		throw InvalidOperationException("Can't compare types \"" + std::string(typeNames[a->getType()]) + "\" and \"" + std::string(typeNames[b->getType()]) + "\"");
	result = ((Bool*)ret)->getValue();
	delete ret;
	return result;
	
}
Type* sort(Type* other)
{
	if (other->getType() == LIST)
		std::sort(((List*)other)->getContent().begin(), ((List*)other)->getContent().end(), compare);
	return new Void();
}

Type* lower(Type* other)
{
	if (other->getType() == _CHAR)
		return new Char(tolower(((Char*)other)->getValue()));
	else if (other->getType() == STRING)
	{
		std::string toConvert = ((String*)other)->getContent();
		for (char& c : toConvert)
			c = tolower(c);
		return new String(toConvert);
	}
	else
		throw SyntaxException("lower can only be used for a char or a string");
}

Type* upper(Type* other)
{
	if (other->getType() == _CHAR)
		return new Char(toupper(((Char*)other)->getValue()));
	else if (other->getType() == STRING)
	{
		std::string toConvert = ((String*)other)->getContent();
		for (char& c : toConvert)
			c = toupper(c);
		return new String(toConvert);
	}
	else
		throw SyntaxException("lower can only be used for a char or a string");
}

Type* ret(Type* other)
{
	throw ReturnException(other->copy());
}

Type* throwFunc(Type* other)
{
	throw other->copy();
}

Type* sleep(Type* other)
{
	if (other->getType() != _INT)
		throw InvalidOperationException("sleep expects 1 int argument");
	std::this_thread::sleep_for(std::chrono::milliseconds(((Int*)other)->getValue()));
	return new Void();
}
