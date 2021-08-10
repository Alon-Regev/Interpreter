#pragma once
#include "Type.h"
#include "Int.h"

#define CHAR "char"

class Char : public Type
{
public:
	Char(const char value);
	Char();
	virtual std::string toString() const;
	virtual Type* copy();
	static bool isType(const std::string& value);
	char getValue();
	// operators
	virtual Type* add(Type* other);
	virtual Type* sub(Type* other);
	virtual Type* assign(Type* other);

	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
	virtual Type* greater(Type* other);
	virtual Type* less(Type* other);
	virtual Type* greaterEqual(Type* other);
	virtual Type* lessEqual(Type* other);

	// casting
	virtual Type* toInt();
private:
	char _value;
};

