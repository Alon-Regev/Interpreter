#pragma once
#include "Type.h"

class Void : public Type
{
public:
	Void();
	virtual std::string toString() const;
	virtual Type* copy();
	static bool isType(const std::string& value);
};

