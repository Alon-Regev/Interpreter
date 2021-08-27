#pragma once
#include "InterpreterException.h"
class SyntaxException : public InterpreterException
{
public:
	SyntaxException(const std::string& message, int lineNumber = DEFAULT_LINE_NUMBER) : 
		InterpreterException("SyntaxError: " + message, lineNumber) 
	{
	}
};

