#pragma once
#include "Type.h"
#include "Tuple.h"

#define STATIC_FUNCTION "staticFunction"

typedef Type* (*staticFunction)(Type*);
typedef Type*(*staticMethod)(Type*, Type*);

class StaticFunction : public Type
{
public:
	StaticFunction(staticFunction function);
	virtual std::string toString() const { return STATIC_FUNCTION; }
	virtual Type* copy();
	static bool isType(const std::string& value) { return false; }
	void setThis(Type* value, bool deletePrev = true);
	// operators
	virtual Type* call(Type* other);
private:
	staticFunction _function;
	Type* _this = nullptr;
};

