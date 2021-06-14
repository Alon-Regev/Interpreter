#pragma once
#include <string>
#include "InvalidOperationException.h"

class Type
{
public:
	Type(std::string type, bool staticType=false) : _type(type), _staticType(staticType) {}
	virtual std::string toString() = 0;
	virtual Type* copy() = 0;
	const std::string& getType() const;
	bool isStaticType() const;
	void setStatic();
	void setVariable(const std::string& variableName);
	std::string getVariable();
	bool isVariable();
	// operators
	virtual Type* add(Type* other);
	virtual Type* sub(Type* other);
	virtual Type* div(Type* other);
	virtual Type* mul(Type* other);
	virtual Type* assign(Type* other);
	virtual Type* call(Type* other);
	virtual Type* block(Type* other);
protected:
	std::string _type;
	bool _staticType;
	std::string _variable = "";
};

