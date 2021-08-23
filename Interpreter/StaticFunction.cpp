#include "StaticFunction.h"

StaticFunction::StaticFunction(staticFunction function) : Type(STATIC_FUNCTION), _function(function)
{
}

Type* StaticFunction::copy()
{
    return new StaticFunction(this->_function);
}

void StaticFunction::setThis(Type* value, bool deletePrev)
{
    if(deletePrev)
        delete this->_this;
    this->_this = value;
}

Type* StaticFunction::call(Type* other)
{
    if(this->_this)
        return ((staticMethod)this->_function)(other, this->_this);
    else
        return this->_function(other);
}
