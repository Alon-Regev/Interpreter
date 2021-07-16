#pragma once
#include <vector>
#include "Type.h"

#define TEMP_SEQUENCE "ts"

class TempSequence : public Type
{
public:
	TempSequence();
	virtual ~TempSequence();
	TempSequence(std::vector<Type*>& values);
	virtual std::string toString() const;
	virtual Type* copy();
	virtual void extend(Type* value);
	virtual std::vector<Type*>::iterator begin();
	virtual std::vector<Type*>::iterator end();
	virtual void clear();
private:
	std::vector<Type*> _values;
};

