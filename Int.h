#pragma once
#include "Type.h"
#include <regex>

#define INT "int"
#define INT_DEFAULT_VALUE 0

class Int : public Type
{
public:
	Int(const std::string& value);
	Int(const int value);
	Int();
	virtual std::string toString();
	virtual Type* copy();
	static bool isType(const std::string& value);
	// operators
	virtual Type* add(Type* other);
	virtual Type* sub(Type* other);
	virtual Type* div(Type* other);
	virtual Type* mul(Type* other);
	virtual Type* assign(Type* other);
private:
	int _value;
};

