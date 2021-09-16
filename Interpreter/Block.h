#pragma once
#include "Type.h"
#include "Interpreter.h"

class Interpreter;
class Block : public Type
{
public:
	Block(Interpreter& interpreter, Node* node, std::map<std::string, Type*>& parentVariables, bool sameScope=false);
	virtual ~Block();
	virtual std::string toString() const { return typeNames[BLOCK]; }
	virtual Type* copy();
	static bool isType(const std::string& value) { return false; }
	Node* getCode();
	Interpreter& getInterpreter();
	Type* run();
	std::vector<Node*> split();
	std::map<std::string, Type*>& getVariables();
	std::map<std::string, Type*>& getParentVariables();
private:
	Node* _code;
	Interpreter& _interpreter;
	std::map<std::string, Type*> _variables;
	std::map<std::string, Type*>& _parentVariables;
	bool _sameScope;
};

