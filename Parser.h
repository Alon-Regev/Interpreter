#pragma once
#include "Node.h"
#include "Type.h"
#include <string>
#include <stack>
#include <vector>
#include <map>
#include "SyntaxException.h"
#include "Helper.h"

enum opTypes{BINARY_INFIX, UNARY_PREFIX, UNARY_POSTFIX};

typedef Type*(*operation)(Type*, Type*);
struct Operator
{
	operation func;
	int order;
	char type = BINARY_INFIX;
};

template<class EvaluationType>
class Parser : public Node
{
public:
	Parser(const std::map<std::string, Operator>& operators);
    EvaluationType value(const std::string& expression); 
    EvaluationType value(Node* expression);
protected:
    virtual EvaluationType valueOf(const std::string& leaf) = 0;
    virtual EvaluationType evaluateBlock(Node* node) = 0;
private:
	Node* parse(const std::string& expression);
	Node* parse(std::vector<Node*>& expr, bool removeParentheses=true);
	void removeParentheses(std::vector<Node*>& expr);
	EvaluationType evaluate(Node*);

	int isOperator(Node* node);
	int isOperator(std::string s);
	std::string findOperator(std::string);
	bool isOpenParentheses(char c);
    bool isCloseParentheses(char c);
    std::string getParentheses(char c);

    const std::map<std::string, Operator>& _operators;
};

// constructor
template<class EvaluationType>
Parser<EvaluationType>::Parser(const std::map<std::string, Operator>& operators) : Node(""), _operators(operators)
{
}

template<class EvaluationType>
inline EvaluationType Parser<EvaluationType>::value(const std::string& expression)
{    
    Node* tree = this->parse(expression);
    EvaluationType result = this->evaluate(tree);
    delete tree;
    return result;
}

template<class EvaluationType>
inline EvaluationType Parser<EvaluationType>::value(Node* expression)
{
    return this->evaluate(expression);
}

// function evaluates a subtree
template<class EvaluationType>
EvaluationType Parser<EvaluationType>::evaluate(Node* node)
{
    if (node == nullptr)
        return 0;
    else if (node->isLeaf())
    {
        // is a value
        return this->valueOf(node->_value);
    }
    else
    {
        if (node->_block)
            return this->evaluateBlock(node);
        // is an operator
        EvaluationType lv = evaluate(node->_left);
        EvaluationType rv = evaluate(node->_right);
        std::string op = node->_value;
        if (this->_operators.find(op) == this->_operators.end())
            throw SyntaxException("Can't parse operators");
        return this->_operators.at(op).func(lv, rv);
    }
}

// function parses string
template<class EvaluationType>
Node* Parser<EvaluationType>::parse(const std::string& expression)
{
    // put expression on expr
    std::vector<Node*> expr;
    std::string::const_iterator it;
    std::string value = "", op = "";
    bool expectingOperator = false;
    // copy string chars as nodes
    for (it = expression.begin(); it != expression.end(); it++)
    {
        // check if char is start of an operator
        op = this->findOperator(std::string(it, expression.end()));
        if (this->isOpenParentheses(*it))
        {
            if (expectingOperator)   // parentheses operator
            {
                Helper::trim(value);
                expr.push_back(new Node(value));
                value = "";
                expr.push_back(new Node(this->getParentheses(*it))); // parentheses operator
                expr.push_back(new Node(std::string(1, *it)));
                expectingOperator = false;
            }
            else    // regular parentheses
            {
                Helper::trim(value);
                if (value != "")
                    expr.push_back(new Node(value));
                value = "";
                expr.push_back(new Node(std::string(1, *it)));
                expectingOperator = false;
            }
        }
        else if (this->isCloseParentheses(*it))
        {
            Helper::trim(value);
            expr.push_back(new Node(value));
            value = "";
            expr.push_back(new Node(std::string(1, *it)));
            expectingOperator = true;
        }
        else if (op == "")   // not an operator, part of value
        {
            value += *it;
            if(value != " ")
                expectingOperator = true;
        }
        else
        {   // is an operator, push value and operator
            Helper::trim(value);
            if (value != "")   // not empty
                expr.push_back(new Node(value));
            // push operator
            expr.push_back(new Node(op));
            it += op.length() - 1;  // skip over operator
            value = "";
            expectingOperator = false;
        }
    }
    Helper::trim(value);
    if (value != "") // add last value
        expr.push_back(new Node(value));
    // remove empties
    for (int i = 0; i < expr.size(); i++)
        if (expr[i]->_value.find_first_not_of(' ') == std::string::npos) // is space
                expr.erase(expr.begin() + i--);
    return this->parse(expr);
}

// function parses expression <expr>
template<class EvaluationType>
Node* Parser<EvaluationType>::parse(std::vector<Node*>& expr, bool removeParentheses)
{
    if (expr.size() == 1)
        return expr.back();
    if (expr.size() == 0)
        return nullptr;
    // process entire expression. turn parentheses into one node.
    if (removeParentheses)
    {
        this->removeParentheses(expr);
        if (expr.size() == 1)  // everything was in parentheses
            return expr[0];
    }

    // evaluate operators
    int i = 0;
    int lastOperator = 0;   // find operator which will be executed last
    for (i = expr.size() - 1; i >= 0; i--) // go over tokens from end to start
    {
        // still haven't picked operator || current operator has lower order
        if (!isOperator(expr[lastOperator]) || isOperator(expr[i]) && isOperator(expr[i]) < isOperator(expr[lastOperator]))
        {   // new last operator
            lastOperator = i;
        }
    }
    // parse two sides of <lastOperator>
    // 1st operand
    std::vector<Node*> operand(expr.begin(), expr.begin() + lastOperator);
    expr[lastOperator]->_left = this->parse(operand, false);
    // 2nd operand
    operand = std::vector<Node*>(expr.begin() + lastOperator + 1, expr.end());  // 1nd part
    expr[lastOperator]->_right = this->parse(operand, false);

    return expr[lastOperator];
}

// function removes parentheses from expression. It turns them into one single node.
template<class EvaluationType>
void Parser<EvaluationType>::removeParentheses(std::vector<Node*>& expr)
{
    while (true)
    {
        std::vector<Node*>::iterator it, lastParentheses = expr.end(); // last open parentheses '('
        for (it = expr.begin(); it != expr.end(); it++)
        {
            if ((*it)->_value.length() == 1 && this->isOpenParentheses((*it)->_value[0]))
                lastParentheses = it;
            else if ((*it)->_value.length() == 1 && this->isCloseParentheses((*it)->_value[0]))
                break;  // found sub expression
        }
        if (it == expr.end())
            break;  // no parentheses at all in expression
        // get sub-expression
        std::vector<Node*> subExpression(lastParentheses + 1, it);
        Node* newNode = this->parse(subExpression);
        // delete sub-expression from expr and insert new node
        if ((*lastParentheses)->_value == "{")
            newNode->_block = true;
        expr.erase(lastParentheses + 1, it + 1);
        if (newNode != nullptr)
        {
            **lastParentheses = *newNode;
            delete newNode;
        }
        else
        {
            *lastParentheses = new Node("");
        }
    }
}

// function checks if a node is an operator.
// returns 0 if not operator (a value), else returns operator's order
template<class EvaluationType>
int Parser<EvaluationType>::isOperator(Node* node)
{
    if (!node->isLeaf()) // operators must be leaves
        return 0;
    return isOperator(node->_value);
}
template<class EvaluationType>
int Parser<EvaluationType>::isOperator(std::string s)
{
    if (this->_operators.find(s) == this->_operators.end())   // not an operator
        return 0;
    else    // find order
        return this->_operators.at(s).order;
}

// function finds longest operator which starts at substring
template<class EvaluationType>
std::string Parser<EvaluationType>::findOperator(std::string substring)
{
    bool found = false;
    while (substring != "")
    {
        if (this->_operators.find(substring) != this->_operators.end())    // is an operator
            break;  // found 
        substring.pop_back();   // else pop string and try again
    }
    return substring;
}

template<class EvaluationType>
inline bool Parser<EvaluationType>::isOpenParentheses(char c)
{
    return c == '(' || c == '{';
}

template<class EvaluationType>
inline bool Parser<EvaluationType>::isCloseParentheses(char c)
{
    return c == ')' || c == '}';
}

template<class EvaluationType>
inline std::string Parser<EvaluationType>::getParentheses(char c)
{
    if (c == '(' || c == ')')
        return "()";
    else if (c == '{' || c == '}')
        return "{}";
}
