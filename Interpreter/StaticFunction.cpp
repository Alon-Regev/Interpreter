#include "StaticFunction.h"

StaticFunction::StaticFunction(staticFunction function) : Type(STATIC_FUNCTION), _function(function)
{
}

Type* StaticFunction::call(Type* other)
{
    return this->_function(other);
}
