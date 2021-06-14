#include "TypeErrorException.h"

TypeErrorException::TypeErrorException(const std::string& message)
{
    this->message = "TypeError: " + message;
}

const char* TypeErrorException::what() const
{
    return this->message.c_str();
}
