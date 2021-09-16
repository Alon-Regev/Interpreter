#pragma once
#include <regex>
#include <map>

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

typedef Type* (*staticFunction)(Type*);

struct ScopeVariable
{
	std::string name;
	Type* previousValue = nullptr;
};

class Function;
class Block;
class Tuple;
class Interpreter : public Parser
{
public:
	Interpreter(bool debugMode = false);
	~Interpreter();
	std::string run(const std::string& code);
	void importFunctions(const std::map<std::string, staticFunction>&);
	void importVariables(const std::map<std::string, Type*>&);
	static Type* assign(Type* a, Type* b, std::map<std::string, Type*>& variables);
	static void removeVariable(const std::string& name, std::map<std::string, Type*>& variables, bool deleteValue = true);
	static Type* addVariable(std::string variableName, std::map<std::string, Type*>& variables, Type* variable, bool isNew = false, bool setScope = false, bool setStatic = true);
	static void checkAssign(Type* type);
	static Type* catchBlock(Type* a, Type* b, std::map<std::string, Type*>& variables);

	static std::vector<Type*> getArgs(Type* other, bool checkList = false);
	static double getNumber(Type* other);

	void printVariables();
	static std::map<std::string, Type*> _variables;
	static Type* createFunction(Type* a, Type* b, std::map<std::string, Type*>& variables);
	static Type* constValue(const std::string& str);
protected:
	virtual Type* valueOf(const std::string& str, std::map<std::string, Type*>& variables);
	virtual std::string getValue(const std::string& expression);
	virtual Type* evaluateBlock(Node* node, std::map<std::string, Type*>& variables);
	virtual Type* handleParentheses(Type* value, char parenthesesType);
	virtual void handleTempTypes(Type* a, Type* b, Type* res, const std::string& op);
	virtual void debug(int lineNumber, std::map<std::string, Type*>& variables);
private:
	static std::map<std::string, Operator> _operators;
	static std::vector<std::vector<ScopeVariable>> _variableScope;
	bool _debugMode = false;
	Type* checkNewVariable(const std::string& str, std::map<std::string, Type*>& variables);
	static TempSequence* sequenceExtension(Type* a, Type* b);
	static bool isVariableNameValid(const std::string& name);
};

