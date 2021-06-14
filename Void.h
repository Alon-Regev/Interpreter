#pragma once
#include "Type.h"

#define VOID "void"

class Void : public Type
{
public:
	Void();
	virtual std::string toString();
	virtual Type* copy();
	static bool isType(const std::string& value);
};

