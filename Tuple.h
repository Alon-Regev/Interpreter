#pragma once
#include "Type.h"
#include <vector>
#include "Interpreter.h"

#define TUPLE "tuple"

class Tuple : public Type
{
public:
	Tuple();
	virtual std::string toString() const;
	virtual Type* copy() { return nullptr; }
	static bool isType(const std::string& value) { return false; }
	void extend(Type* type);
	bool isVariableTuple();
	std::vector<Type*>::const_iterator begin();
	std::vector<Type*>::const_iterator end();
	// operators
	virtual Type* assign(Type* other);
private:
	std::vector<Type*> _values;
};

