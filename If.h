#pragma once
#include "Type.h"
#include "Bool.h"
#include "Block.h"
#include "Signal.h"

#define IF "if"
#define ELSE_SIGNAL "elseSignal"

class If : public Type
{
public:
	If(Type* condition);
	virtual std::string toString() { return IF; }
	virtual Type* copy() { return nullptr; }
	static bool isType(const std::string& value) { return false; }
	// operators
	virtual Type* block(Type* other);
	// else
	static Type* elseCheck(Type* ifReturn, Type* block);
private:
	bool _condition;
};

