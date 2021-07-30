#pragma once
#include "Type.h"
#include <regex>
#include "Bool.h"

#define INT "int"
#define INT_DEFAULT_VALUE 0

class Int : public Type
{
public:
	Int(const std::string& value);
	Int(const int value);
	Int();
	virtual std::string toString() const;
	virtual Type* copy();
	static bool isType(const std::string& value);
	int getValue();
	// operators
	virtual Type* add(Type* other);
	virtual Type* sub(Type* other);
	virtual Type* div(Type* other);
	virtual Type* mul(Type* other);
	virtual Type* negative();
	virtual Type* assign(Type* other);

	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
	virtual Type* greater(Type* other);
	virtual Type* less(Type* other);
	virtual Type* greaterEqual(Type* other);
	virtual Type* lessEqual(Type* other);
private:
	int _value;
};

