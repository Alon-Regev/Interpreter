#pragma once
#include "Type.h"

class Undefined : public Type
{
public:
	Undefined();
	virtual std::string toString() const;
	virtual Type* copy();
	static bool isType(const std::string& value);
};

