#pragma once
#include "Type.h"
#include "Tuple.h"

#define FOREACH "foreach"

class Foreach : public Type
{
public:
	Foreach(Type* parameters);
	virtual std::string toString() const { return FOREACH; }
	virtual Type* copy() { return nullptr; }
	// operators
	virtual Type* block(Type* other);
private:
	Type* _current;
	Type* _container;
};

