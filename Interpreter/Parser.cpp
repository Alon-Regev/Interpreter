#include "Parser.h"

// constructor
Parser::Parser(const std::map<std::string, Operator>& operators) : Node(), _operators(operators)
{
}

Type* Parser::value(const std::string& expression, std::map<std::string, Type*>& variables)
{
    Node* tree = nullptr;
    Type* result = nullptr;
    std::vector<Node*> temp = this->tokenize(expression);
    try
    {
        tree = this->parse(temp);
    }
    catch (std::exception& e)
    {
        for (Node* node : temp)
            delete node;
        throw;
    }
    try
    {
        result = this->evaluate(tree, variables);
    }
    catch (std::exception& e)
    {
        delete tree;
        throw;
    }
    delete tree;
    return result;
}

Type* Parser::value(Node* expression, std::map<std::string, Type*>& variables)
{
    return this->evaluate(expression, variables);
}

// function evaluates a subtree
Type* Parser::evaluate(Node* node, std::map<std::string, Type*>& variables)
{
    if (node == nullptr)
        return 0;
    else if (node->isLeaf())
    {
        // is a value
        Type* temp = this->valueOf(node->_value, variables);
        if (node->getParentheses() != 0)
            temp = this->handleParentheses(temp, node->getParentheses());
        return temp;
    }
    else
    {
        if (node->getParentheses() == '{' && !this->isObject(node))
            return this->evaluateBlock(node, variables);
        // is an operator
        Type* lv = evaluate(node->_left, variables);
        Type* rv = nullptr;
        try
        {
            rv = evaluate(node->_right, variables);
        }
        catch (...)
        {
            if (lv)
                lv->tryDelete();
            throw;
        }
        std::string op = node->_value;
        if (this->_operators.find(op) == this->_operators.end())
            throw SyntaxException("Can't parse operators");
        Operator _operator = this->_operators.at(op);
        if (!_operator.allowNulls && (rv == nullptr && _operator.type == UNARY_PREFIX || lv == nullptr && _operator.type == UNARY_POSTFIX || (lv == nullptr || rv == nullptr) && _operator.type == BINARY_INFIX))
        {
            if(rv)
                rv->tryDelete();
            if (lv)
                lv->tryDelete();
            throw SyntaxException(INVALID_OPERATOR_USE(op));
        }

        Type* temp = nullptr;
        try
        {
            if(_operator.accessVariables)
                temp = ((variablesOperation)this->_operators.at(op).func)(lv, rv, variables);
            else
                temp = this->_operators.at(op).func(lv, rv);
        }
        catch (...)
        {
            if (rv)
                rv->tryDelete();
            if (lv)
                lv->tryDelete();
            throw;
        }
        this->handleTempTypes(lv, rv, temp, op);
        // handle special parentheses
        if (node->getParentheses() != 0)
            temp = this->handleParentheses(temp, node->getParentheses());
        return temp;
    }
}

// function tokenizes string -> vector<Node*>
std::vector<Node*> Parser::tokenize(const std::string& expression)
{
    // put expression on expr
    std::vector<Node*> expr;
    std::string::const_iterator it;
    std::string op = "";
    bool expectingOperator = false;
    int lineNumber = 1;

    // copy string chars as nodes
    for (it = expression.begin(); it != expression.end(); it++)
    {
        // skip white space
        if (*it == ' ' || *it == '\t')    
            continue;
        if (*it == '\n')
        {
            lineNumber++;
            continue;
        }
        // check if char is start of an operator
        op = this->findOperator(std::string(it, expression.end()));
        if (op != "")   // not an operator, and not value
        {
            expr.push_back(new Node(op, lineNumber));
            it += op.size() - 1;
            expectingOperator = false;
            continue;
        }
        // check if char is value
        std::string value = this->getValue(std::string(it, expression.end()));
        if (value != "")
        {
            expr.push_back(new Node(value, lineNumber));
            it += value.size() - 1;
            expectingOperator = true;
        }
        else if (this->isOpenParentheses(*it))
        {
            if (expectingOperator)   // parentheses operator
                expr.push_back(new Node(this->getParentheses(*it)));
            expr.push_back(new Node(std::string(1, *it), lineNumber));
            expectingOperator = false;
        }
        else if (this->isCloseParentheses(*it))
        {
            expr.push_back(new Node(std::string(1, *it), lineNumber));
            expectingOperator = true;
        }
        else
        {
            // clear memory and throw exception
            for (Node* n : expr)
                delete n;
            throw SyntaxException(std::string("Unknown value ") + *it + " at index " + std::to_string(it - expression.begin()));
        }
    }
    // remove empties
    for (int i = 0; i < expr.size(); i++)
    {
        if (expr[i]->_value.find_first_not_of(' ') == std::string::npos) // is space
        {
            delete expr[i];
            expr.erase(expr.begin() + i--);
        }
    }
    return expr;
}

// function parses expression <expr>
Node* Parser::parse(std::vector<Node*>& expr, bool removeParentheses)
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
        // still haven't picked operator || current operator has lower order
        if (!isOperator(expr[lastOperator]) || isOperator(expr[i]) && (isOperator(expr[i]) < isOperator(expr[lastOperator]) || !isLTR(expr[i]) && isOperator(expr[i]) == isOperator(expr[lastOperator])))
            // new last operator
            lastOperator = i;
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
void Parser::removeParentheses(std::vector<Node*>& expr)
{
    // loop breaks when there are no more parentheses
    while (true)
    {
        std::vector<Node*>::iterator it,
            openParentheses = expr.end(),
            closeParentheses;
        // go over expression and find open and close parentheses
        for (it = expr.begin(); it != expr.end(); it++)
        {
            // check if node is open parentheses
            if ((*it)->_value.length() == 1 && this->isOpenParentheses((*it)->_value[0]))
                openParentheses = it;
            // check if node is close parentheses
            else if ((*it)->_value.length() == 1 && this->isCloseParentheses((*it)->_value[0]))
                break;  // found sub expression
        }
        closeParentheses = it;
        // check if parentheses were found
        if (closeParentheses == expr.end())
        {
            if (openParentheses == expr.end())
                break;  // no parentheses at all in expression
            else
                throw SyntaxException("opening parentheses without closing parentheses");
        }
        // check if open parentheses are valid
        if (openParentheses == expr.end())
            throw SyntaxException("closing parentheses without opening parentheses");
        // get sub expression tree in parentheses
        std::vector<Node*> subExpression(openParentheses + 1, closeParentheses);
        Node* newNode = this->parse(subExpression);
        // fill parentheses character in subtree
        char parenthesesChar = (*openParentheses)->_value[0];
        if (this->isOpenParentheses(parenthesesChar) && newNode != nullptr)
            newNode->setParentheses(parenthesesChar);

        // delete sub-expression from expr and insert parsed tree
        // delete parentheses nodes
        delete(*it); 
        delete(*openParentheses);
        expr.erase(openParentheses + 1, closeParentheses + 1);
        // check if there's a subtree
        if (newNode != nullptr)
        {
            // copy subtree to node
            *openParentheses = newNode;
        }
        else
        {   // no subtree
            // put empty node instead of parentheses
            *openParentheses = new Node();
            (*openParentheses)->setParentheses(parenthesesChar);
        }
    }
}

// function checks if a node is an operator.
// returns 0 if not operator (a value), else returns operator's order
int Parser::isOperator(Node* node)
{
    if (!node->isLeaf()) // operators must be leaves
        return 0;
    return isOperator(node->_value);
}
int Parser::isOperator(std::string s)
{
    if (this->_operators.find(s) == this->_operators.end())   // not an operator
        return 0;
    else    // find order
        return this->_operators.at(s).order;
}

int Parser::isLTR(Node* node)
{
    if (this->_operators.find(node->_value) == this->_operators.end())   // not an operator
        return 0;
    else    // find order
        return this->_operators.at(node->_value).ltr;
}

// function finds longest operator which starts at substring
std::string Parser::findOperator(std::string substring)
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

bool Parser::isOpenParentheses(char c)
{
    return c == '(' || c == '{' || c == '[';
}

bool Parser::isCloseParentheses(char c)
{
    return c == ')' || c == '}' || c == ']';
}

std::string Parser::getParentheses(char c)
{
    if (c == '(' || c == ')')
        return "(^)";
    else if (c == '{' || c == '}')
        return "{^}";
    else if (c == '[' || c == ']')
        return "[^]";
}

bool Parser::isObject(Node* node)
{
    if (node->_value == ",")
    {
        if ((node->_left->_value == "," && this->isObject(node->_left) || node->_left->_value == ":") && node->_right->_value == ":")
            return true;
        else return false;
    }
    else if (node->_value == ":")
        return true;
    return false;
}
