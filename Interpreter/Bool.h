#pragma once
#include "Type.h"

#define _BOOL "bool"	// _BOOL for solving conflict with WinAPI
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
	// operators
	virtual Type* assign(Type* other);
	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
	virtual Type* logicOr(Type* other);
	virtual Type* logicAnd(Type* other);
private:
	bool _value;
};

