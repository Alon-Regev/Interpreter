#include "Type.h"

const std::string& Type::getType() const
{
    return this->_type;
}

bool Type::isStaticType() const
{
    return this->_staticType;
}

void Type::setStatic()
{
    this->_staticType = true;
}

void Type::setVariable(const std::string& variableName)
{
    this->_variable = variableName;
}

std::string Type::getVariable()
{
    return this->_variable;
}

bool Type::isVariable()
{
    return this->_variable != "";
}

Type* Type::add(Type* other)
{
    throw InvalidOperationException("+ between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::sub(Type* other)
{
    throw InvalidOperationException("- between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::div(Type* other)
{
    throw InvalidOperationException("/ between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::mul(Type* other)
{
    throw InvalidOperationException("* between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::assign(Type* other)
{
    throw InvalidOperationException("= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::call(Type* other)
{
    throw InvalidOperationException("() between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::block(Type* other)
{
    throw InvalidOperationException("{} between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

