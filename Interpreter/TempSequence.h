#pragma once
#include <vector>
#include "Type.h"

class TempSequence : public Type
{
public:
	TempSequence();
	virtual ~TempSequence();
	TempSequence(std::vector<Type*>& values);
	virtual std::string toString() const;
	virtual Type* copy();
	virtual void sequenceExtend(Type* value);
	virtual std::vector<Type*>::iterator begin();
	virtual std::vector<Type*>::iterator end();
	virtual void clear();
	std::vector<Type*>& getValues();
private:
	std::vector<Type*> _values;
};

