#pragma once
#include "Type.h"
#include "VariableException.h"

#define REFERENCE "ref"

class Reference : public Type
{
public:
	Reference();
	Reference(Type* other);
	virtual std::string toString() const;
	virtual Type* copy();
	virtual Type* getValue();
	// operators
	virtual Type* add(Type* other);
	virtual Type* sub(Type* other);
	virtual Type* div(Type* other);
	virtual Type* mul(Type* other);
	virtual Type* assign(Type* other);
	virtual Type* call(Type* other);
	virtual Type* block(Type* other);
	virtual Type* index(Type* other);
	virtual Type* negative();
	// logic operators
	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
	virtual Type* greater(Type* other);
	virtual Type* less(Type* other);
	virtual Type* greaterEqual(Type* other);
	virtual Type* lessEqual(Type* other);
	virtual Type* logicOr(Type* other);
	virtual Type* logicAnd(Type* other);
private:
	Type* _value;
	void checkReference() const;
};

