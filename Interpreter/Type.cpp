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
    if (other->getType() == REFERENCE)
        return this->add(((Reference*)other)->getValue());
    throw InvalidOperationException("+ between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::sub(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->sub(((Reference*)other)->getValue());
    throw InvalidOperationException("- between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::div(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->div(((Reference*)other)->getValue());
    throw InvalidOperationException("/ between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::mul(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->mul(((Reference*)other)->getValue());
    throw InvalidOperationException("* between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::mod(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->mod(((Reference*)other)->getValue());
    throw InvalidOperationException("% between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::exp(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->exp(((Reference*)other)->getValue());
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
    if (other->getType() == REFERENCE)
        return this->ternary(((Reference*)other)->getValue());
    throw InvalidOperationException("? between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::xorAssign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->xorAssign(((Reference*)other)->getValue());
    throw InvalidOperationException("^= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::andAssign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->andAssign(((Reference*)other)->getValue());
    throw InvalidOperationException("&= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::orAssign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->orAssign(((Reference*)other)->getValue());
    throw InvalidOperationException("|= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::leftShiftAssign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->leftShiftAssign(((Reference*)other)->getValue());
    throw InvalidOperationException("<<= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::rightShiftAssign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->rightShiftAssign(((Reference*)other)->getValue());
    throw InvalidOperationException(">>= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::extendAssign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->extendAssign(((Reference*)other)->getValue());
    throw InvalidOperationException("<-= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::bitXor(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->bitXor(((Reference*)other)->getValue());
    throw InvalidOperationException("^ between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::bitAnd(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->bitAnd(((Reference*)other)->getValue());
    throw InvalidOperationException("& between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::bitOr(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->bitOr(((Reference*)other)->getValue());
    throw InvalidOperationException("| between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::bitNot()
{
    throw InvalidOperationException("~ to type \"" + this->_type + "\"");
}

Type* Type::leftShift(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->leftShift(((Reference*)other)->getValue());
    throw InvalidOperationException("<< between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::rightShift(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->rightShift(((Reference*)other)->getValue());
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
    if (other->getType() == REFERENCE)
        return this->addAssign(((Reference*)other)->getValue());
    throw InvalidOperationException("+= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::subAssign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->subAssign(((Reference*)other)->getValue());
    throw InvalidOperationException("-= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::divAssign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->divAssign(((Reference*)other)->getValue());
    throw InvalidOperationException("/= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::mulAssign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->mulAssign(((Reference*)other)->getValue());
    throw InvalidOperationException("*= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::modAssign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->modAssign(((Reference*)other)->getValue());
    throw InvalidOperationException("%= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::expAssign(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->expAssign(((Reference*)other)->getValue());
    throw InvalidOperationException("**= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::call(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->call(((Reference*)other)->getValue());
    throw InvalidOperationException("() between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::block(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->block(((Reference*)other)->getValue());
    throw InvalidOperationException("{} between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::index(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->index(((Reference*)other)->getValue());
    throw InvalidOperationException("[] between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::point(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->point(((Reference*)other)->getValue());
    throw InvalidOperationException(". between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::extend(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->extend(((Reference*)other)->getValue());
    throw InvalidOperationException("-> between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::negative()
{
    throw InvalidOperationException("- to type \"" + this->_type + '"');
}

Type* Type::equal(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->equal(((Reference*)other)->getValue());
    return new Bool(false);
}

Type* Type::notEqual(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->notEqual(((Reference*)other)->getValue());
    return new Bool(true);
}

Type* Type::greater(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->greater(((Reference*)other)->getValue());
    throw InvalidOperationException("> between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::less(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->less(((Reference*)other)->getValue());
    throw InvalidOperationException("< between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::greaterEqual(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->greaterEqual(((Reference*)other)->getValue());
    throw InvalidOperationException(">= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::lessEqual(Type* other)
{
    if (other->getType() == REFERENCE)
        return this->lessEqual(((Reference*)other)->getValue());
    throw InvalidOperationException("<= between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::logicOr (Type * other)
{
    if (other->getType() == REFERENCE)
        return this->logicOr(((Reference*)other)->getValue());
    throw InvalidOperationException("|| between types \"" + this->_type + "\" and \"" + other->_type + "\"");
}

Type* Type::logicAnd (Type* other)
{
    if (other->getType() == REFERENCE)
        return this->logicAnd(((Reference*)other)->getValue());
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

