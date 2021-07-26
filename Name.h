#pragma once
#include "Type.h"
#include "Undefined.h"

#define NAME "name"

class Name : public Type
{
public:
	Name(const std::string& str);
	virtual std::string toString() const;
	virtual Type* copy();
	std::string _name;
};

