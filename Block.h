#pragma once
#include "Type.h"
#include "Interpreter.h"

#define BLOCK "block"

class Interpreter;
class Block : public Type
{
public:
	Block(Interpreter& interpreter, Node* node);
	virtual ~Block();
	virtual std::string toString() const { return BLOCK; }
	virtual Type* copy();
	static bool isType(const std::string& value) { return false; }
	Node* getCode();
	Interpreter& getInterpreter();
	Type* run();
private:
	Node* _code;
	Interpreter& _interpreter;
};

