#pragma once
#include "Object.h"
#include "Reference.h"
#include "Function.h"

class Class : public Object
{
public:
	Class();
	Class(const std::string name, std::map<std::string, Type*> variables);
	// operators
	virtual Type* assign(Type* other);
	virtual Type* call(Type* other);
};

