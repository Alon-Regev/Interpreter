#pragma once
#include "Type.h"
#include "VariableException.h"

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

	virtual Type* call(Type* other);
	virtual Type* block(Type* other);
	virtual Type* index(Type* other);
	virtual Type* point(Type* other);
	virtual Type* extend(Type* other);
	virtual Type* negative();
	// assignment
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

	virtual Type* extendAssign(Type* other);
	// logic operators
	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
	virtual Type* greater(Type* other);
	virtual Type* less(Type* other);
	virtual Type* greaterEqual(Type* other);
	virtual Type* lessEqual(Type* other);
	virtual Type* logicOr(Type* other);
	virtual Type* logicAnd(Type* other);
	virtual Type* logicNot();

	// casting
	virtual Type* toInt();
	virtual Type* toBool();
	virtual Type* toFloat();
	virtual Type* toChar();
private:
	Type* _value;
	void checkReference() const;
};

