#include "Parser.h"

// constructor
Parser::Parser(const std::map<std::string, Operator>& operators) : Node(""), _operators(operators)
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
        // on error clear memory
        for (Node* node : temp)
            delete node;
        throw;
    }
    try
    {
        // evaluate tree
        result = this->evaluate(tree, variables);
    }
    catch (std::exception& e)
    {
        // delete tree on error
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
        if (node->_block != 0)
            temp = this->handleParentheses(temp, node->_block);
        return temp;
    }
    else
    {
        if (node->_block == '{' && !this->isObject(node))
            return this->evaluateBlock(node, variables);
        // is an operator
        std::string op = node->_value;
        if (this->_operators.find(op) == this->_operators.end())
            throw SyntaxException("Can't parse operators");
        Operator _operator = this->_operators.at(op);

        // evaluate left node
        Type* lv = nullptr;
        if(_operator.leftBlock) // evaluate as block
            lv = evaluateBlock(node->_left, variables);
        else    // evaluate fully
            lv = evaluate(node->_left, variables);
        Type* rv = nullptr;
        try
        {
            if (_operator.rightBlock) // evaluate as block
                rv = evaluateBlock(node->_right, variables);
            else    // evaluate fully
                rv = evaluate(node->_right, variables);
        }
        catch (...)
        {
            // error when evaluating right node, clear allocated memory
            if (lv)
                lv->tryDelete();
            throw;
        }

        // check if nodes aren't null (if nulls aren't allowed)
        if (!_operator.allowNulls && (rv == nullptr && _operator.type == UNARY_PREFIX || lv == nullptr && _operator.type == UNARY_POSTFIX || (lv == nullptr || rv == nullptr) && _operator.type == BINARY_INFIX))
        {
            // on error clear memory
            if(rv)
                rv->tryDelete();
            if (lv)
                lv->tryDelete();
            throw SyntaxException(INVALID_OPERATOR_USE(op));
        }
        // compute operation
        Type* temp = nullptr;
        try
        {
            // pass scope variables to operator function if needed
            if(_operator.accessVariables)
                temp = ((variablesOperation)this->_operators.at(op).func)(lv, rv, variables);
            else    // regular operator
                temp = this->_operators.at(op).func(lv, rv);
        }
        catch (...)
        {
            // clear memory on operator error
            if (rv)
                rv->tryDelete();
            if (lv)
                lv->tryDelete();
            throw;
        }
        // handle temporary left and right node evaluations
        this->handleTempTypes(lv, rv, temp, op);
        // handle special parentheses
        if (node->_block != 0)
            temp = this->handleParentheses(temp, node->_block);
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

    // copy string chars as nodes
    for (it = expression.begin(); it != expression.end(); it++)
    {
        if (*it == ' ' || *it == '\n' || *it == '\t')    // white space
            continue;
        // check if char is start of an operator
        op = this->findOperator(std::string(it, expression.end()));
        if (op != "")   // not an operator, and not value
        {
            expr.push_back(new Node(op));
            it += op.size() - 1;
            expectingOperator = false;
            continue;
        }
        // check if char is value
        std::string value = this->getValue(std::string(it, expression.end()));
        if (value != "")
        {
            expr.push_back(new Node(value));
            it += value.size() - 1;
            expectingOperator = true;
        }
        else if (this->isOpenParentheses(*it))
        {
            if (expectingOperator)   // parentheses operator
                expr.push_back(new Node(this->getParentheses(*it)));
            expr.push_back(new Node(std::string(1, *it)));
            expectingOperator = false;
        }
        else if (this->isCloseParentheses(*it))
        {
            expr.push_back(new Node(std::string(1, *it)));
            expectingOperator = true;
        }
        else
        {
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
        {
            if (lastParentheses == expr.end())
                break;  // no parentheses at all in expression
            else
                throw SyntaxException("opening parentheses without closing parentheses");
        }
        // get sub-expression
        if (lastParentheses == expr.end())
            throw SyntaxException("closing parentheses without opening parentheses");
        std::vector<Node*> subExpression(lastParentheses + 1, it);
        Node* newNode = this->parse(subExpression);
        // delete sub-expression from expr and insert new node
        char lp = (*lastParentheses)->_value[0];
        if (isOpenParentheses(lp) && newNode != nullptr)
            newNode->_block = lp;
        delete(*it);
        expr.erase(lastParentheses + 1, it + 1);

        if (newNode != nullptr)
        {
            **lastParentheses = *newNode;
            delete newNode;
        }
        else
        {
            if (*lastParentheses)
                delete (*lastParentheses);
            *lastParentheses = new Node("");
            if (isOpenParentheses(lp))
                (*lastParentheses)->_block = lp;
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
    // returns parentheses operator string
    if (c == '(' || c == ')')
        return "(^)";
    else if (c == '{' || c == '}')
        return "{^}";
    else if (c == '[' || c == ']')
        return "[^]";
}

bool Parser::isObject(Node* node)
{
    // checks whether a node contains an object initialization
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
