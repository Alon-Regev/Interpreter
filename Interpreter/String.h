#pragma once
#include "Sequence.h"

#define STRING "string"

class String : public Sequence<char>
{
public:
	String();
	String(std::vector<char> content);
	String(std::string content);
	virtual std::string toString() const;
	virtual Type* copy();
	static bool isType(const std::string& value);
	// operators
	virtual Type* add(Type* other);

	// casting
	virtual Type* toInt();
	virtual Type* toBool();
	virtual Type* toFloat();
protected:
	virtual Type* toType(char value);
};

