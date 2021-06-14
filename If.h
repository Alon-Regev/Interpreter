#pragma once
#include "Type.h"
#include "Bool.h"
#include "Block.h"

#define IF "if"

class If : public Type
{
public:
	If(Type* condition);
	virtual std::string toString() { return IF; }
	virtual Type* copy() { return nullptr; }
	static bool isType(const std::string& value) { return false; }
	// operators
	virtual Type* block(Type* other);
private:
	bool _condition;
};

