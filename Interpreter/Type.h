#pragma once
#include <string>
#include <map>
#include "InvalidOperationException.h"

#ifdef _DEBUG
	#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#define TYPES 24
enum typeId { _INT, _CHAR, _BOOL, _FLOAT, STRING, LIST, REFERENCE, OBJECT, CLASS, PAIR, BLOCK, FOR, FOREACH, FUNCTION, IF, NAME, SIGNAL, STATIC_FUNCTION, TEMP_SEQUENCE, TUPLE, UNDEFINED, _VOID, WHILE, ANY };
extern const char* typeNames[];
extern std::map<std::string, short> nameTypes;

class Type
{
public:
	Type(short type, bool staticType=false) : _type(type), _staticType(staticType) {}
	virtual ~Type() = default;
	virtual std::string toString() const = 0;
	virtual Type* copy() = 0;
	short getType() const;
	bool isStaticType() const;
	void setStatic();
	void setVariable(const std::string& variableName);
	std::string getVariable();
	bool isVariable();
	Type* temp();
	// method moves the responsibility on the type forward (makes sure it won't be deleted)
	Type* useValue();
	bool checkDelete();

	virtual void set(void*) {}
	// operators
	virtual Type* add(Type* other);
	virtual Type* sub(Type* other);
	virtual Type* div(Type* other);
	virtual Type* mul(Type* other);
	virtual Type* mod(Type* other);
	virtual Type* exp(Type* other);

	virtual Type* increment(bool post);
	virtual Type* decrement(bool post);

	virtual Type* ternary(Type* other);

	virtual Type* bitXor (Type* other);
	virtual Type* bitAnd (Type* other);
	virtual Type* bitOr (Type * other);
	virtual Type* bitNot();
	virtual Type* leftShift(Type* other);
	virtual Type* rightShift(Type* other);

	virtual Type* call(Type* other);
	virtual Type* block(Type* other);
	virtual Type* index(Type* other);
	virtual Type* point(Type* other);
	virtual Type* extend(Type* other);
	virtual Type* negative();
	// assignment
	virtual Type* assign(Type* other);

	virtual Type* addAssign(Type* other);
	virtual Type* subAssign(Type* other);
	virtual Type* divAssign(Type* other);
	virtual Type* mulAssign(Type* other);
	virtual Type* modAssign(Type* other);
	virtual Type* expAssign(Type* other);

	virtual Type* xorAssign (Type* other);
	virtual Type* andAssign (Type* other);
	virtual Type* orAssign (Type * other);
	virtual Type* leftShiftAssign(Type* other);
	virtual Type* rightShiftAssign(Type* other);

	virtual Type* extendAssign(Type* other);
	// logic operators
	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
	virtual Type* greater(Type* other);
	virtual Type* less(Type* other);
	virtual Type* greaterEqual(Type* other);
	virtual Type* lessEqual(Type* other);
	virtual Type* logicOr (Type* other);
	virtual Type* logicAnd(Type* other);
	virtual Type* logicNot();

	// casting
	virtual Type* toInt();
	virtual Type* toBool();
	virtual Type* toFloat();
	virtual Type* toChar();

	Type* tryReference();
	void tryDelete();
protected:
	short _type;
	bool _staticType;
	bool _delete = true;
	bool _temp = false;
	std::string _variable = "";

	bool typeCompare(Type* other);
};

