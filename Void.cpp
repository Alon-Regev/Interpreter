#include "Void.h"

Void::Void() : Type(VOID)
{
}

std::string Void::toString()
{
    return "";
}

Type* Void::copy()
{
    return new Void();
}

bool Void::isType(const std::string& value)
{
    return value == "void";
}
