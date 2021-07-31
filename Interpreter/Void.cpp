#include "Void.h"

Void::Void() : Type(VOID)
{
}

std::string Void::toString() const
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
