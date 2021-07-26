#pragma once
#include "Object.h"
#include "Reference.h"
#include "Function.h"

#define CLASS "class"

class Class : public Object
{
public:
	Class();
	// operators
	virtual Type* assign(Type* other);
	virtual Type* call(Type* other);
};

