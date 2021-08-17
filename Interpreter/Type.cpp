#include "Type.h"
#include "String.h"
#include "Reference.h"

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

Type* Type::mod(Type* other)
{
    throw InvalidOperationException("% between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::exp(Type* other)
{
    throw InvalidOperationException("** between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::increment(bool post)
{
    throw InvalidOperationException("++ to type \"" + this->_type + "\"");
}

Type* Type::decrement(bool post)
{
    throw InvalidOperationException("-- to type \"" + this->_type + "\"");
}

Type* Type::ternary(Type* other)
{
    throw InvalidOperationException("? between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::xorAssign(Type* other)
{
    throw InvalidOperationException("^= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::andAssign(Type* other)
{
    throw InvalidOperationException("&= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::orAssign(Type* other)
{
    throw InvalidOperationException("|= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::leftShiftAssign(Type* other)
{
    throw InvalidOperationException("<<= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::rightShiftAssign(Type* other)
{
    throw InvalidOperationException(">>= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::extendAssign(Type* other)
{
    throw InvalidOperationException("<-= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::bitXor(Type* other)
{
    throw InvalidOperationException("^ between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::bitAnd(Type* other)
{
    throw InvalidOperationException("& between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::bitOr(Type* other)
{
    throw InvalidOperationException("| between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::bitNot()
{
    throw InvalidOperationException("~ to type \"" + this->_type + "\"");
}

Type* Type::leftShift(Type* other)
{
    throw InvalidOperationException("<< between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::rightShift(Type* other)
{
    throw InvalidOperationException(">> between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::assign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->assign(((Reference*)other)->getValue());
    throw InvalidOperationException("= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::addAssign(Type* other)
{
    throw InvalidOperationException("+= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::subAssign(Type* other)
{
    throw InvalidOperationException("-= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::divAssign(Type* other)
{
    throw InvalidOperationException("/= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::mulAssign(Type* other)
{
    throw InvalidOperationException("*= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::modAssign(Type* other)
{
    throw InvalidOperationException("%= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::expAssign(Type* other)
{
    throw InvalidOperationException("**= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
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

Type* Type::point(Type* other)
{
    throw InvalidOperationException(". between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::extend(Type* other)
{
    throw InvalidOperationException("-> between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::negative()
{
    throw InvalidOperationException("- to type \"" + this->_type + '"');
}

Type* Type::equal(Type* other)
{
    return new Bool(false);
}

Type* Type::notEqual(Type* other)
{
    return new Bool(true);
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

Type* Type::logicNot()
{
    throw InvalidOperationException("! to type \"" + this->_type + "\"");
}

Type* Type::toInt()
{
    throw InvalidOperationException("casting " + this->_type + " to int");
}

Type* Type::toBool()
{
    throw InvalidOperationException("casting " + this->_type + " to bool");
}

Type* Type::toFloat()
{
    throw InvalidOperationException("casting " + this->_type + " to float");
}

Type* Type::toChar()
{
    throw InvalidOperationException("casting " + this->_type + " to char");
}

Type* Type::tryReference()
{
    return this->isVariable() ? new Reference(this) : this->copy();
}

void Type::tryDelete()
{
    if (!this->isVariable())
        delete this;
}

bool Type::typeCompare(Type* other)
{
    return this->_type == other->_type;
}

