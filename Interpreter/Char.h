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
	virtual Type* bitXor(Type* other);
	virtual Type* bitAnd(Type* other);
	virtual Type* bitOr(Type* other);
	virtual Type* bitNot();

	virtual Type* assign(Type* other);

	virtual Type* addAssign(Type* other);
	virtual Type* subAssign(Type* other);
	virtual Type* xorAssign(Type* other);
	virtual Type* andAssign(Type* other);
	virtual Type* orAssign(Type* other);

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

