#include "Tuple.h"

Tuple::Tuple() : Type(TUPLE)
{
}

std::string Tuple::toString() const
{
    if (this->_values.empty())
        return "()";
    std::string res = "(";
    for (Type* type : this->_values)
    {
        res += type->toString() + ", ";
    }
    res.pop_back();
    res.pop_back();
    return res + ")";
}

void Tuple::extend(Type* type)
{
    this->_values.push_back(type);
}

bool Tuple::isVariableTuple()
{
    // for a tuple to be assignable, all values have to be variables
    for (Type*& value : this->_values)
        if (!value->isVariable())
            return false;
    return true;
}

std::vector<Type*>::const_iterator Tuple::begin()
{
    return this->_values.begin();
}

std::vector<Type*>::const_iterator Tuple::end()
{
    return this->_values.end();
}

const std::vector<Type*>& Tuple::getValues()
{
    return this->_values;
}

Type* Tuple::assign(Type* other)
{
    if (other->getType() != TUPLE)
        return Type::assign(other);
    Tuple* otherTuple = (Tuple*)other;
    // check tuple size
    if (this->_values.size() != otherTuple->_values.size())
        throw InvalidOperationException("assigning tuples in different sizes");
    // assign values one by one
    for (int i = 0; i < this->_values.size(); i++)
        Interpreter::assign(this->_values[i], otherTuple->_values[i]);
    return this;
}
