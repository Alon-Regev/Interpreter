#pragma once
#include <regex>

#include "Parser.h"
#include "PredefinedFunctions.h"

#include "TypeErrorException.h"
#include "VariableException.h"

#include "Function.h"
#include "Block.h"
#include "Void.h"
#include "Undefined.h"
#include "Int.h"
#include "Bool.h"
#include "If.h"
#include "List.h"
#include "TempSequence.h"

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
	virtual Type* handleParentheses(Type* value, char parenthesesType);
private:
	static std::map<std::string, Operator> _operators;
	static std::map<std::string, Type*> _variables;
	static Type* addVariable(std::string variableName, Type* variable, bool isNew=false);
	Type* checkNewVariable(const std::string& str);
	static TempSequence* sequenceExtension(Type* a, Type* b);
	static bool isVariableNameValid(const std::string& name);
};

