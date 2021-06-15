#pragma once
#include "Type.h"

#define STATIC_FUNCTION "staticFunction"

typedef Type*(*staticFunction)(Type*);

class StaticFunction : public Type
{
public:
	StaticFunction(staticFunction function);
	virtual std::string toString() const { return STATIC_FUNCTION; }
	virtual Type* copy() { return nullptr; }
	static bool isType(const std::string& value) { return false; }
	// operators
	virtual Type* call(Type* other);
private:
	staticFunction _function;
};

