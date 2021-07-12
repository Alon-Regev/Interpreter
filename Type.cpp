#include "Type.h"
#include "String.h"

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
    if (other->getType() == STRING)
        return new String(this->toString() + other->toString());
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

Type* Type::index(Type* other)
{
    throw InvalidOperationException("[] between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::negative()
{
    throw InvalidOperationException("- to type \"" + this->_type + '"');
}

Type* Type::equal(Type* other)
{
    throw InvalidOperationException("== between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::notEqual(Type* other)
{
    throw InvalidOperationException("!= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::greater(Type* other)
{
    throw InvalidOperationException("> between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::less(Type* other)
{
    throw InvalidOperationException("< between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::greaterEqual(Type* other)
{
    throw InvalidOperationException(">= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::lessEqual(Type* other)
{
    throw InvalidOperationException("<= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::logicOr (Type * other)
{
    throw InvalidOperationException("|| between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::logicAnd (Type* other)
{
    throw InvalidOperationException("&& between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

bool Type::typeCompare(Type* other)
{
    return this->_type == other->_type;
}

