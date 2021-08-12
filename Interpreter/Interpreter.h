#pragma once
#include <regex>

#define ANY "var"

#include "Parser.h"
#include "PredefinedFunctions.h"

#include "TypeErrorException.h"
#include "VariableException.h"

#include "Function.h"
#include "Block.h"
#include "Void.h"
#include "Undefined.h"
#include "Int.h"
#include "Float.h"
#include "Bool.h"
#include "If.h"
#include "List.h"
#include "TempSequence.h"
#include "Char.h"
#include "String.h"
#include "While.h"
#include "Foreach.h"
#include "For.h"
#include "Reference.h"
#include "Pair.h"
#include "Object.h"
#include "Name.h"
#include "Class.h"

struct ScopeVariable
{
	std::string name;
	Type* previousValue = nullptr;
};

class Function;
class Block;
class Tuple;
class Interpreter : public Parser<Type*>
{
public:
	Interpreter();
	~Interpreter();
	std::string run(const std::string& code);
	void importFunctions(const std::map<std::string, staticFunction>&);
	static Type* assign(Type* a, Type* b);
	static void removeVariable(const std::string& name);
	static void openScope();
	static void closeScope();
	static Type* addVariable(std::string variableName, Type* variable, bool isNew = false, bool setScope = false);
	static void checkAssign(Type* type);
protected:
	virtual Type* valueOf(const std::string& str);
	virtual Type* evaluateBlock(Node* node);
	virtual std::string getValue(const std::string& expression);
	virtual Type* handleParentheses(Type* value, char parenthesesType);
	virtual void handleTempTypes(Type* a, Type* b, Type* res, const std::string& op);
private:
	static std::map<std::string, Operator> _operators;
	static std::map<std::string, Type*> _variables;
	static std::vector<std::vector<ScopeVariable>> _variableScope;
	Type* checkNewVariable(const std::string& str);
	static TempSequence* sequenceExtension(Type* a, Type* b);
	static bool isVariableNameValid(const std::string& name);
};

