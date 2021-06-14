#pragma once
#include "Type.h"

#define BOOL "bool"
#define FALSE "false"
#define TRUE "true"

class Bool : public Type
{
public:
	Bool(const std::string& value);
	Bool(bool value);
	Bool();
	virtual std::string toString();
	virtual Type* copy();
	static bool isType(const std::string& value);
	bool getValue();
	// operators
	virtual Type* assign(Type* other);
private:
	bool _value;
};

