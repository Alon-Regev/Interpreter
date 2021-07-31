#pragma once
#include "InterpreterException.h"

class VariableException : public InterpreterException
{
public:
    VariableException(const std::string& message) : InterpreterException("TypeError: " + message) {}
};

