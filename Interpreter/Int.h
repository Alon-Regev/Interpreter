#pragma once
#include "Type.h"
#include <regex>
#include "Bool.h"
#include "Float.h"
#include "Char.h"

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
	virtual void set(void*);
	// operators
	virtual Type* add(Type* other);
	virtual Type* sub(Type* other);
	virtual Type* div(Type* other);
	virtual Type* mul(Type* other);
	virtual Type* negative();
	virtual Type* mod(Type* other);
	virtual Type* exp(Type* other);

	virtual Type* increment(bool post);
	virtual Type* decrement(bool post);

	virtual Type* bitXor(Type* other);
	virtual Type* bitAnd(Type* other);
	virtual Type* bitOr(Type* other);
	virtual Type* bitNot();
	virtual Type* leftShift(Type* other);
	virtual Type* rightShift(Type* other);

	virtual Type* assign(Type* other);
	virtual Type* addAssign(Type* other);
	virtual Type* subAssign(Type* other);
	virtual Type* divAssign(Type* other);
	virtual Type* mulAssign(Type* other);
	virtual Type* modAssign(Type* other);
	virtual Type* expAssign(Type* other);

	virtual Type* xorAssign(Type* other);
	virtual Type* andAssign(Type* other);
	virtual Type* orAssign(Type* other);
	virtual Type* leftShiftAssign(Type* other);
	virtual Type* rightShiftAssign(Type* other);

	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
	virtual Type* greater(Type* other);
	virtual Type* less(Type* other);
	virtual Type* greaterEqual(Type* other);
	virtual Type* lessEqual(Type* other);

	// casting
	virtual Type* toBool();
	virtual Type* toFloat();
	virtual Type* toChar();
private:
	int _value;
};

