#pragma once
#include <exception>
#include <string>

class InterpreterException : public std::exception
{
public:
    InterpreterException(const std::string& message) : _message(message) {}
    virtual const char* what() const override { return this->_message.c_str(); }
private:
    std::string _message;
};

