#pragma once
#include "Type.h"

class Signal : public Type
{
public:
	Signal(short value);
	virtual std::string toString() const;
	virtual Type* copy();
	short getValue() const;
private:
	short _value;
};

