#pragma once
#include "Type.h"
#include "Node.h"
#include "Interpreter.h"
#include "Tuple.h"
#include "Block.h"
#include "TypeErrorException.h"

class Interpreter;
class Block;
class Tuple;

struct Parameter
{
	std::string name;
	short type;
};

struct FunctionInstance
{
	std::vector<Parameter> parameters;
	Block* function;
};

class Function : public Type
{
public:
	Function(Interpreter& interpreter);
	Function(Type* params, Block* block, std::map<std::string, Type*>& variables);
	Function(std::vector<FunctionInstance>& functionInstances, Interpreter& interpreter, Type* thisType);
	virtual ~Function();
	virtual std::string toString() const { return typeNames[FUNCTION]; }
	virtual Type* copy();
	void setThis(Type* value, bool deletePrev = true);
	// operators
	virtual Type* call(Type* other);
	virtual Type* assign(Type* other);

	virtual Type* extend(Type* other);
	virtual Type* extendAssign(Type* other);
private:
	std::vector<FunctionInstance> _functionInstances;
	Interpreter& _interpreter;
	Type* _this = nullptr;

	Type* run(FunctionInstance& function, std::vector<Type*>& args);
};

