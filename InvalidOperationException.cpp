#include "InvalidOperationException.h"

InvalidOperationException::InvalidOperationException(const std::string& message)
{
    this->message = "InvalidOperationError: " + message;
}

const char* InvalidOperationException::what() const
{
    return this->message.c_str();
}
