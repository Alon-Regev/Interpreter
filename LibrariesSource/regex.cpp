#include "Implementation.h"

// Add names of exported functions and variables here...
const std::vector<std::string> functions = { "match", "search", "replace", "findAll" };
const std::map<std::string, Type*> variables = {};

// Define your functions here...

DLLEXPORT Type* match(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other);
	if (args.size() != 2)
		throw InvalidOperationException("regex match expects 2 parameters");
	if(args[0]->getType() != STRING || args[1]->getType() != STRING)
		throw InvalidOperationException("regex match expects string arguments");
	// search in regex
	std::smatch regexMatch;
	std::regex regex;
	try
	{
		regex = std::regex(args[1]->toString());
	}
	catch (...)
	{
		throw InvalidOperationException("Invalid regex");
	}
	std::string searchIn = args[0]->toString();
	if (!std::regex_match(searchIn, regexMatch, regex))
		return new Undefined();
	// extract groups
	if (regexMatch.size() == 1)
		return new String(regexMatch[0].str());
	else
	{
		List* result = new List();
		for (int i = 0; i < regexMatch.size(); i++)
			result->push(new String(regexMatch[i].str()));
		return result;
	}
}

DLLEXPORT Type* search(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other);
	if (args.size() != 2)
		throw InvalidOperationException("regex search expects 2 parameters");
	if (args[0]->getType() != STRING || args[1]->getType() != STRING)
		throw InvalidOperationException("regex search expects string arguments");
	// search in regex
	std::smatch regexMatch;
	std::regex regex;
	try
	{
		regex = std::regex(args[1]->toString());
	}
	catch (...)
	{
		throw InvalidOperationException("Invalid regex");
	}
	std::string searchIn = args[0]->toString();
	if (!std::regex_search(searchIn, regexMatch, regex))
		return new Undefined();
	// extract groups
	if (regexMatch.size() == 1)
		return new String(regexMatch[0].str());
	else
	{
		List* result = new List();
		for (int i = 0; i < regexMatch.size(); i++)
			result->push(new String(regexMatch[i].str()));
		return result;
	}
}

DLLEXPORT Type* replace(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other);
	if (args.size() != 3)
		throw InvalidOperationException("regex match expects 3 parameters");
	if (args[0]->getType() != STRING || args[1]->getType() != STRING || args[2]->getType() != STRING)
		throw InvalidOperationException("regex match expects string arguments");
	// search in regex
	std::regex regex;
	try
	{
		regex = std::regex(args[1]->toString());
	}
	catch (...)
	{
		throw InvalidOperationException("Invalid regex");
	}
	std::string replaceIn = args[0]->toString();
	std::string replaceBy = args[2]->toString();
	// replace and return replaced string
	return new String(std::regex_replace(replaceIn, regex, replaceBy));
}

DLLEXPORT Type* findAll(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other);
	if (args.size() != 2)
		throw InvalidOperationException("regex findAll expects 2 parameters");
	if (args[0]->getType() != STRING || args[1]->getType() != STRING)
		throw InvalidOperationException("regex findAll expects string arguments");
	// search in regex
	std::smatch regexMatch;
	std::regex regex;
	try
	{
		regex = std::regex(args[1]->toString());
	}
	catch (...)
	{
		throw InvalidOperationException("Invalid regex");
	}
	std::string searchIn = args[0]->toString();
	List* ret = new List();
	// as long as results keep showing up
	std::string::const_iterator searchStart(searchIn.cbegin());
	while (std::regex_search(searchStart, searchIn.cend(), regexMatch, regex))
	{
		// extract groups
		if (regexMatch.size() == 1)
			ret->push(new String(regexMatch[0].str()));
		else
		{
			List* result = new List();
			for (int i = 0; i < regexMatch.size(); i++)
				result->push(new String(regexMatch[i].str()));
			ret->push(result);
		}
		searchStart = regexMatch.suffix().first;
	}
	return ret;
}
