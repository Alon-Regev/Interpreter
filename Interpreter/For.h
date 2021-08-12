#pragma once
#include "Type.h"
#include "Block.h"

#define FOR "for"

class For : public Type
{
public:
	For(Type* param);
	virtual ~For();
	virtual std::string toString() const { return FOR; }
	virtual Type* copy() { return nullptr; }
	// operators
	virtual Type* block(Type* other);

	bool runCondition();
private:
	Block* _start;
	Block* _condition;
	Block* _end;
};

