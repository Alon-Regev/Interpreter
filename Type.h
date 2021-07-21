#pragma once
#include <string>
#include "InvalidOperationException.h"

#ifdef _DEBUG
	#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

class Type
{
public:
	Type(std::string type, bool staticType=false) : _type(type), _staticType(staticType) {}
	virtual ~Type() = default;
	virtual std::string toString() const = 0;
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
	virtual Type* index(Type* other);
	virtual Type* point(Type* other);
	virtual Type* negative();
	// logic operators
	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
	virtual Type* greater(Type* other);
	virtual Type* less(Type* other);
	virtual Type* greaterEqual(Type* other);
	virtual Type* lessEqual(Type* other);
	virtual Type* logicOr (Type* other);
	virtual Type* logicAnd(Type* other);
protected:
	std::string _type;
	bool _staticType;
	std::string _variable = "";

	bool typeCompare(Type* other);
};

