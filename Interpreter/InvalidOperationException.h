#pragma once
#include "InterpreterException.h"

class InvalidOperationException : public InterpreterException
{
public:
    InvalidOperationException(const std::string& message) : InterpreterException("InvalidOperationError: " + message) {}
};

