#pragma once
#include <vector>
#include "Type.h"

#define TEMP_SEQUENCE "ts"

class TempSequence : public Type
{
public:
	TempSequence();
	TempSequence(std::vector<Type*>& values);
	virtual std::string toString() const;
	virtual Type* copy();
	virtual void extend(Type* value);
	virtual std::vector<Type*>::reverse_iterator begin();
	virtual std::vector<Type*>::reverse_iterator end();
private:
	std::vector<Type*> _values;
};

