#include "TempSequence.h"

TempSequence::TempSequence() : Type(TEMP_SEQUENCE)
{
}

TempSequence::~TempSequence()
{
    for (Type*& type : this->_values)
        if(!type->isVariable())
            delete type;
}

TempSequence::TempSequence(std::vector<Type*>& values) : Type(TEMP_SEQUENCE)
{
    this->_values.assign(values.begin(), values.end());
}

std::string TempSequence::toString() const
{
    return "temp sequence";
}

Type* TempSequence::copy()
{
    return new TempSequence(this->_values);
}

void TempSequence::extend(Type* value)
{
    this->_values.push_back(value);
}

std::vector<Type*>::iterator TempSequence::begin()
{
    return this->_values.begin();
}

std::vector<Type*>::iterator TempSequence::end()
{
    return this->_values.end();
}

void TempSequence::clear()
{
    this->_values.clear();
}
