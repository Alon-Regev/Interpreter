#pragma once
#include "Node.h"
#include "Type.h"
#include <string>
#include <stack>
#include <vector>
#include <map>
#include "SyntaxException.h"
#include "Helper.h"

#include <iostream>

#ifdef _DEBUG
    #define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

#define INVALID_OPERATOR_USE(op) "invalid operator use of operator \"" + op + '"'

enum opTypes{BINARY_INFIX, UNARY_PREFIX, UNARY_POSTFIX};

typedef Type*(*operation)(Type*, Type*);
struct Operator
{
	operation func;
	int order;
	char type = BINARY_INFIX;
    bool allowNulls = false;    // true if func checks for nulls
    bool ltr = true;   // is evaluated Left To Right or Right To Left
};

class Parser : public Node
{
public:
	Parser(const std::map<std::string, Operator>& operators);
    Type* value(const std::string& expression); 
    Type* value(Node* expression);
protected:
    virtual Type* valueOf(const std::string& leaf) = 0;
    virtual Type* evaluateBlock(Node* node) = 0;
    virtual std::string getValue(const std::string& expression) = 0;
    virtual Type* handleParentheses(Type* value, char parenthesesType) { return value; }
    virtual void handleTempTypes(Type*, Type*, Type*, const std::string& op) {}
private:
	std::vector<Node*> tokenize(const std::string& expression);
	Node* parse(std::vector<Node*>& expr, bool removeParentheses=true);
	void removeParentheses(std::vector<Node*>& expr);
	Type* evaluate(Node*);

	int isOperator(Node* node);
	int isOperator(std::string s);
    int isLTR(Node* node);
	std::string findOperator(std::string);
	bool isOpenParentheses(char c);
    bool isCloseParentheses(char c);
    std::string getParentheses(char c);
    bool isObject(Node* node);

    const std::map<std::string, Operator>& _operators;
};
