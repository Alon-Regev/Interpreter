#include "Interpreter.h"

std::map<std::string, Operator> Interpreter::_operators = {
	{"+", Operator{[](Type* a, Type* b) { return a->add(b); }, 9} },
	{"-", Operator{[](Type* a, Type* b) { return a->sub(b); }, 9} },
	{"*", Operator{[](Type* a, Type* b) { return a->mul(b); }, 10} },
	{"/", Operator{[](Type* a, Type* b) { return a->div(b); }, 10} },

	{"()", Operator{[](Type* a, Type* b) { return a->call(b); }, 11} },
	
	{",", Operator{(operation)Interpreter::tupleExtension, 5} },
	{"=>", Operator{[](Type* a, Type* b) { return (Type*)new Function(a, (Block*)b); }, 5} },

	{"=", Operator{(operation)Interpreter::assign, 4} },

	{"if", Operator{[](Type* a, Type* b) { return (Type*)new If(b); }, 3, UNARY_PREFIX}},
	{"else", Operator{[](Type* a, Type* b) { return If::elseCheck(a, b); }, 1}},
	{"{}", Operator{[](Type* a, Type* b) { return a->block(b); }, 2} },

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
	// invalid expression
	else
		throw TypeErrorException("Value \"" + str + "\" cannot be parsed");
}

Type* Interpreter::evaluateBlock(Node* node)
{
	return new Block(*this, node);
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
	if (isNew && Interpreter::_variables.find(variableName) != Interpreter::_variables.end())
		throw VariableException('"' + variableName + "\" already exists");
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
	else
		return nullptr;
	staticType->setStatic();
	return staticType;
}

Tuple* Interpreter::tupleExtension(Type* a, Type* b)
{
	if (a->getType() == TUPLE)
	{
		((Tuple*)a)->extend(b);
		return (Tuple*)a;
	}
	Tuple* tuple = new Tuple();
	tuple->extend(a);
	tuple->extend(b);
	return tuple;
}
