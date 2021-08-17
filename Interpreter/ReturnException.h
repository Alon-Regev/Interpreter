#pragma once
#include <exception>
#include "Type.h"

class ReturnException : public std::exception
{
public:
    ReturnException(Type* value) : _value(value) {}
    virtual const char* what() const override { return "returned"; }
    Type* getValue() { return this->_value; }
private:
    Type* _value;
};
