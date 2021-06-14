#pragma once
#include "InterpreterException.h"

class TypeErrorException : public InterpreterException
{
public:
    TypeErrorException(const std::string& message) : InterpreterException("TypeError: " + message) {}
};

