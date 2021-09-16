#pragma once
#include "List.h"
#include "Int.h"
#include "Char.h"
#include "Float.h"
#include "Bool.h"
#include "Undefined.h"

class String : public Type
{
public:
	String();
	String(std::string content);
	virtual std::string toString() const;
	virtual Type* copy();
	static bool isType(const std::string& value);
	// operators
	virtual Type* add(Type* other);
	virtual Type* assign(Type* other);
	virtual Type* index(Type* other);
	virtual Type* addAssign(Type* other);
	// logic operators
	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);

	// casting
	virtual Type* toInt();
	virtual Type* toBool();
	virtual Type* toFloat();
	virtual Type* toChar();

	const std::string& getContent();
	void setContent(const std::string& content);
private:
	std::string _content;
};

