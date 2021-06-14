#pragma once
#include "Type.h"

#define SIGNAL "signal"

class Signal : public Type
{
public:
	Signal(const std::string& value);
	virtual std::string toString();
	virtual Type* copy();
	const std::string& getValue();
private:
	std::string _value;
};

