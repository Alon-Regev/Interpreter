#include "Char.h"
#include "String.h"

Char::Char(const char value) : Type(CHAR), _value(value)
{
}

Char::Char() : Type(CHAR), _value(0)
{
}

std::string Char::toString() const
{
    return std::string(1, this->_value);
}

Type* Char::copy()
{
    return new Char(this->_value);
}

bool Char::isType(const std::string& value)
{
    return value.size() == 3 && value[0] == '\'' && value.back() == '\'';
}

char Char::getValue()
{
    return this->_value;
}

Type* Char::add(Type* other)
{
    if (other->getType() == INT)
        return new Char(this->_value + ((Int*)other)->getValue());
    if (other->getType() == CHAR)
        return new String(std::string{ this->_value, ((Char*)other)->getValue() });
    else
        return Type::add(other);
}

Type* Char::sub(Type* other)
{
    if (other->getType() == INT)
        return new Char(this->_value - ((Int*)other)->getValue());
    else if (other->getType() == CHAR)
        return new Int(this->_value - ((Char*)other)->getValue());
    else
        return Type::sub(other);
}

Type* Char::bitXor(Type* other)
{
    if (other->getType() == INT)
        return new Char(this->_value ^ ((Int*)other)->getValue());
    else if (other->getType() == CHAR)
        return new Int(this->_value ^ ((Char*)other)->getValue());
    else
        return Type::bitXor(other);
}

Type* Char::bitAnd(Type* other)
{
    if (other->getType() == INT)
        return new Char(this->_value & ((Int*)other)->getValue());
    else if (other->getType() == CHAR)
        return new Int(this->_value & ((Char*)other)->getValue());
    else
        return Type::bitAnd(other);
}

Type* Char::bitOr(Type* other)
{
    if (other->getType() == INT)
        return new Char(this->_value | ((Int*)other)->getValue());
    else if (other->getType() == CHAR)
        return new Int(this->_value | ((Char*)other)->getValue());
    else
        return Type::bitOr(other);
}

Type* Char::bitNot()
{
    return new Int(~this->_value);
}

Type* Char::assign(Type* other)
{
    if (other->getType() == INT)
    {
        this->_value = ((Int*)other)->getValue();
        return this;
    }
    else if (other->getType() == CHAR)
    {
        this->_value = ((Char*)other)->getValue();
        return this;
    }
    else
        Type::assign(other);
}

Type* Char::addAssign(Type* other)
{
    if (other->getType() == INT)
    {
        this->_value += ((Int*)other)->getValue();
        return this;
    }
    else
        Type::addAssign(other);
}

Type* Char::subAssign(Type* other)
{
    if (other->getType() == INT)
    {
        this->_value -= ((Int*)other)->getValue();
        return this;
    }
    else
        Type::subAssign(other);
}

Type* Char::xorAssign(Type* other)
{
    if (other->getType() == INT)
    {
        this->_value ^= ((Int*)other)->getValue();
        return this;
    }
    else
        Type::xorAssign(other);
}

Type* Char::andAssign(Type* other)
{
    if (other->getType() == INT)
    {
        this->_value &= ((Int*)other)->getValue();
        return this;
    }
    else
        Type::andAssign(other);
}

Type* Char::orAssign(Type* other)
{
    if (other->getType() == INT)
    {
        this->_value |= ((Int*)other)->getValue();
        return this;
    }
    else
        Type::orAssign(other);
}

Type* Char::equal(Type* other)
{
    if (other->getType() == CHAR)
        return new Bool(this->_value == ((Char*)other)->getValue());
    else
        Type::equal(other);
}

Type* Char::notEqual(Type* other)
{
    if (other->getType() == CHAR)
        return new Bool(this->_value != ((Char*)other)->getValue());
    else
        Type::notEqual(other);
}

Type* Char::greater(Type* other)
{
    if (other->getType() == CHAR)
        return new Bool(this->_value > ((Char*)other)->getValue());
    else
        Type::greater(other);
}

Type* Char::less(Type* other)
{
    if (other->getType() == CHAR)
        return new Bool(this->_value < ((Char*)other)->getValue());
    else
        Type::less(other);
}

Type* Char::greaterEqual(Type* other)
{
    if (other->getType() == CHAR)
        return new Bool(this->_value >= ((Char*)other)->getValue());
    else
        Type::greaterEqual(other);
}

Type* Char::lessEqual(Type* other)
{
    if (other->getType() == CHAR)
        return new Bool(this->_value <= ((Char*)other)->getValue());
    else
        Type::lessEqual(other);
}

Type* Char::toInt()
{
    return new Int(this->_value);
}
