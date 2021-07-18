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
	virtual ~Function();
	virtual std::string toString() const { return FUNCTION; }
	virtual Type* copy() { return nullptr; }
	// operators
	virtual Type* call(Type* other);
	virtual Type* assign(Type* other);
private:
	Type* _function;
	Interpreter& _interpreter;
	std::vector<Parameter> _parameters;
};

