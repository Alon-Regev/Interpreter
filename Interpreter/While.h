#pragma once
#include "Type.h"
#include "Bool.h"
#include "Block.h"

#define	WHILE "while"

class While : public Type
{
public:
	While(Type* condition);
	virtual ~While();
	virtual std::string toString() const { return WHILE; }
	virtual Type* copy() { return nullptr; }
	static bool isType(const std::string& value) { return false; }
	// operators
	virtual Type* block(Type* other);
private:
	Type* _condition;

	bool getCondition();
};

