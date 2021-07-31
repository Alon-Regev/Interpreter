#pragma once
#include "Type.h"

#define PAIR "pair"

class Pair : public Type
{
public:
	Pair(Type* a, Type* b);
	virtual ~Pair();
	virtual std::string toString() const;
	virtual Type* copy();

	Type* _first;
	Type* _second;
};

