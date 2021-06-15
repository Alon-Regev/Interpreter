#pragma once
#include "InterpreterException.h"
class SyntaxException : public InterpreterException
{
public:
	SyntaxException(const std::string& message) : InterpreterException("SyntaxError: " + message) {}
};

