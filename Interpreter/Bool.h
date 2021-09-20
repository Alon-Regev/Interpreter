#pragma once
#include "Type.h"
#include "Int.h"
#include "Float.h"
#include "Pair.h"

#define _FALSE "false"
#define _TRUE "true"

class Bool : public Type
{
public:
	Bool(const std::string& value);
	Bool(bool value);
	Bool();
	virtual std::string toString() const;
	virtual Type* copy();
	static bool isType(const std::string& value);
	bool getValue();
	virtual void set(void*);
	// operators
	virtual Type* assign(Type* other);
	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
	virtual Type* logicOr(Type* other);
	virtual Type* logicAnd(Type* other);
	virtual Type* logicNot();

	virtual Type* ternary(Type* other);
	// casting
	virtual Type* toInt();
	virtual Type* toFloat();
private:
	bool _value;
};

