#include "Interpreter.h"

std::map<std::string, Operator> Interpreter::_operators = {
	{"+", Operator{[](Type* a, Type* b) { return a->add(b); }, 9} },
	{"-", Operator{[](Type* a, Type* b) { if (b == nullptr) throw SyntaxException(INVALID_OPERATOR_USE(std::string("-"))); else return a == nullptr ? b->negative() : a->sub(b); }, 9, BINARY_INFIX, true} },
	{"*", Operator{[](Type* a, Type* b) { return a->mul(b); }, 10} },
	{"/", Operator{[](Type* a, Type* b) { return a->div(b); }, 10} },
	{"()", Operator{[](Type* a, Type* b) { return a->call(b); }, 11} },
	
	{",", Operator{(operation)Interpreter::sequenceExtension, 5, BINARY_INFIX, false, true} },
	{"=>", Operator{[](Type* a, Type* b) { return (Type*)new Function(a, (Block*)b); }, 5} },

	{"=", Operator{(operation)Interpreter::assign, 4} },

	{"if", Operator{[](Type* a, Type* b) { return (Type*)new If(b); }, 3, UNARY_PREFIX}},
	{"else", Operator{[](Type* a, Type* b) { return If::elseCheck(a, b); }, 1}},
	{"{}", Operator{[](Type* a, Type* b) { return a->block(b); }, 2} },

	{"[]", Operator{[](Type* a, Type* b) { return a->index(b); }, 11, BINARY_INFIX, false, true} },
	{"while", Operator{[](Type* a, Type* b) { return (Type*)new While(b); }, 3, UNARY_PREFIX}},

	// logic operators
	{"==", Operator{[](Type* a, Type* b) { return a->equal(b); }, 8} },
	{"!=", Operator{[](Type* a, Type* b) { return a->notEqual(b); }, 8} },
	{">", Operator{[](Type* a, Type* b) { return a->greater(b); }, 8} },
	{"<", Operator{[](Type* a, Type* b) { return a->less(b); }, 8} },
	{">=", Operator{[](Type* a, Type* b) { return a->greaterEqual(b); }, 8} },
	{"<=", Operator{[](Type* a, Type* b) { return a->lessEqual(b); }, 8} },
	{"||", Operator{[](Type* a, Type* b) { return a->logicOr(b); }, 7} },
	{"&&", Operator{[](Type* a, Type* b) { return a->logicAnd(b); }, 6} },
};
std::map<std::string, Type*> Interpreter::_variables;

Interpreter::Interpreter() : Parser(Interpreter::_operators)
{
	// predefined
	initVariables(this->_variables);
}

std::string Interpreter::run(const std::string& code)
{
	return this->value(code)->toString();
}

Type* Interpreter::valueOf(const std::string& str)
{
	// is a variable
	Type* newVar = this->checkNewVariable(str);
	if (newVar)
		return newVar;
	else if (this->_variables.find(str) != this->_variables.end())	// old variable
		return Interpreter::_variables[str];
	// is a type
	else if (Void::isType(str))
		return new Void();
	else if (Undefined::isType(str))
		return new Undefined();
	else if (Int::isType(str))
		return new Int(str);
	else if (Bool::isType(str))
		return new Bool(str);
	else if (String::isType(str))
		return new String(str.substr(1, str.size() - 2));
	// invalid expression
	else
		throw TypeErrorException("Value \"" + str + "\" cannot be parsed");
}

Type* Interpreter::evaluateBlock(Node* node)
{
	return new Block(*this, node);
}

Type* Interpreter::handleParentheses(Type* value, char parenthesesType)
{
	if (value->getType() == TEMP_SEQUENCE)
	{
		if (parenthesesType == '(')
			return new Tuple(((TempSequence*)value)->begin(), ((TempSequence*)value)->end());
		else if (parenthesesType == '[')
			return new List(((TempSequence*)value)->begin(), ((TempSequence*)value)->end());
	}
	else if (parenthesesType == '[')	// short list
	{
		if (value->getType() == UNDEFINED)
			return new List();
		else
			return new List(std::vector<Type*>{value});
	}
	return value;
}

Type* Interpreter::assign(Type* a, Type* b)
{
	if (!a->isVariable())
	{
		if (a->getType() == TUPLE && ((Tuple*)a)->isVariableTuple())
		{
			return a->assign(b);
		}
		else
		{
			throw InvalidOperationException("assigning to a non-variable value");
		}
	}
	// regular cases
	if (a->isStaticType())
		return a->assign(b);	// assign operator
	// replace
	return Interpreter::addVariable(a->getVariable(), b->copy());
}

Type* Interpreter::addVariable(std::string variableName, Type* variable, bool isNew)
{
	Helper::trim(variableName);
	if (isNew)
	{
		if (Interpreter::_variables.find(variableName) != Interpreter::_variables.end())
			throw VariableException('"' + variableName + "\" already exists");
		else if (!isVariableNameValid(variableName))
			throw VariableException('"' + variableName + "\" is not a valid name");
	}
	variable->setVariable(variableName);
	return Interpreter::_variables[variableName] = variable;
}

Type* Interpreter::checkNewVariable(const std::string& str)
{
	if (str.empty())
		return new Undefined();
	Type* staticType = nullptr;
	if (str.rfind("var ", 0) == 0)	// new dynamic variable
		return Interpreter::addVariable(str.substr(4), new Undefined(), true);
	else if (str.rfind(INT " ", 0) == 0)
		staticType = Interpreter::addVariable(str.substr(strlen(INT " ")), new Int(), true);
	else if (str.rfind(FUNCTION " ", 0) == 0)
		staticType = Interpreter::addVariable(str.substr(strlen(FUNCTION " ")), new Function(*this), true);
	else if (str.rfind(BOOL " ", 0) == 0)
		staticType = Interpreter::addVariable(str.substr(strlen(BOOL " ")), new Bool());
	else if (str.rfind(LIST " ", 0) == 0)
		staticType = Interpreter::addVariable(str.substr(strlen(LIST " ")), new List());
	else if (str.rfind(STRING " ", 0) == 0)
		staticType = Interpreter::addVariable(str.substr(strlen(STRING " ")), new String());
	else
		return nullptr;
	staticType->setStatic();
	return staticType;
}

TempSequence* Interpreter::sequenceExtension(Type* a, Type* b)
{
	if (a->getType() == TEMP_SEQUENCE)
	{
		((TempSequence*)a)->extend(b);
		return (TempSequence*)a;
	}
	TempSequence* sequence = new TempSequence();
	sequence->extend(a);
	sequence->extend(b);
	return sequence;
}

bool Interpreter::isVariableNameValid(const std::string& name)
{
	return std::regex_match(name, std::regex("[a-zA-Z_][a-zA-Z0-9_]*"));
}
