#pragma once
#include "InterpreterException.h"

class OtherException : public InterpreterException
{
public:
    OtherException(const std::string& message) : InterpreterException("Error: " + message) {}
};

