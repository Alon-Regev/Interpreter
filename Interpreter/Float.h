#pragma once
#include "Type.h"
#include "Int.h"
#include <sstream>

class Float : public Type
{
public:
	Float(const std::string& value);
	Float(const double value);
	Float();
	virtual std::string toString() const;
	virtual Type* copy();
	static bool isType(const std::string& value);
	double getValue();
	virtual void set(void*);
	// operators
	virtual Type* add(Type* other);
	virtual Type* sub(Type* other);
	virtual Type* div(Type* other);
	virtual Type* mul(Type* other);
	virtual Type* exp(Type* other);
	virtual Type* negative();

	virtual Type* assign(Type* other);

	virtual Type* addAssign(Type* other);
	virtual Type* subAssign(Type* other);
	virtual Type* divAssign(Type* other);
	virtual Type* mulAssign(Type* other);
	virtual Type* expAssign(Type* other);

	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
	virtual Type* greater(Type* other);
	virtual Type* less(Type* other);
	virtual Type* greaterEqual(Type* other);
	virtual Type* lessEqual(Type* other);

	// casting
	virtual Type* toInt();
	virtual Type* toBool();
private:
	double _value;
};

