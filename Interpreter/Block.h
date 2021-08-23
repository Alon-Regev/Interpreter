#pragma once
#include "Type.h"
#include "Interpreter.h"

#define BLOCK "block"

class Interpreter;
class Block : public Type
{
public:
	Block(Interpreter& interpreter, Node* node, std::map<std::string, Type*>& parentVariables);
	virtual ~Block();
	virtual std::string toString() const { return BLOCK; }
	virtual Type* copy();
	static bool isType(const std::string& value) { return false; }
	Node* getCode();
	Interpreter& getInterpreter();
	Type* run(bool openScope = true);
	std::vector<Node*> split();
	std::map<std::string, Type*>& getVariables();
private:
	Node* _code;
	Interpreter& _interpreter;
	std::map<std::string, Type*> _variables;
	std::vector<std::string> _parentVariables;
};

