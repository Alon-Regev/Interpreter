#pragma once
#include "Parser.h"

#include "TypeErrorException.h"
#include "VariableException.h"

#include "Function.h"
#include "Block.h"
#include "Void.h"
#include "Undefined.h"
#include "Int.h"
#include "Bool.h"
#include "If.h"

class Function;
class Block;
class Tuple;
class Interpreter : public Parser<Type*>
{
public:
	Interpreter();
	std::string run(const std::string& code);
	static Type* assign(Type* a, Type* b);
protected:
	virtual Type* valueOf(const std::string& str);
	virtual Type* evaluateBlock(Node* node);
private:
	static std::map<std::string, Operator> _operators;
	static std::map<std::string, Type*> _variables;
	static Type* addVariable(std::string variableName, Type* variable, bool isNew=false);
	Type* checkNewVariable(const std::string& str);
	static Tuple* tupleExtension(Type* a, Type* b);
};
