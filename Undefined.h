#pragma once
#include "Type.h"

#define UNDEFINED "undefined"

class Undefined : public Type
{
public:
	Undefined();
	virtual std::string toString();
	virtual Type* copy();
	static bool isType(const std::string& value);
};

