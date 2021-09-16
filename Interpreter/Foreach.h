#pragma once
#include "Type.h"
#include "Tuple.h"

class Foreach : public Type
{
public:
	Foreach(Type* parameters);
	virtual ~Foreach();
	virtual std::string toString() const { return typeNames[FOREACH]; }
	virtual Type* copy() { return nullptr; }
	// operators
	virtual Type* block(Type* other);

	static Type* comprehension(Type* a, Type* b);
private:
	Type* _current;
	Type* _container;
};

