#pragma once
#include "Type.h"
#include "Node.h"
#include "Interpreter.h"
#include "Tuple.h"
#include "Block.h"
#include "TypeErrorException.h"

#define FUNCTION "function"

struct Parameter
{
	std::string name;
	std::string type;
};

class Interpreter;
class Block;
class Tuple;
class Function : public Type
{
public:
	Function(Interpreter& interpreter);
	Function(Type* params, Block* block);
	Function(std::vector<Parameter>& parameters, Type* function, Interpreter& interpreter, Type* thisType);
	virtual ~Function();
	virtual std::string toString() const { return FUNCTION; }
	virtual Type* copy();
	void setThis(Type* value, bool deletePrev = true);
	// operators
	virtual Type* call(Type* other);
	virtual Type* assign(Type* other);
private:
	Type* _function;
	Interpreter& _interpreter;
	std::vector<Parameter> _parameters;
	Type* _this = nullptr;
};

