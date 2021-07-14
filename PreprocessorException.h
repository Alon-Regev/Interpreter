#pragma once
#include "InterpreterException.h"
class PreprocessorException : public InterpreterException
{
public:
	PreprocessorException(const std::string& message) : InterpreterException("PreprocessorError: " + message) {}
};

