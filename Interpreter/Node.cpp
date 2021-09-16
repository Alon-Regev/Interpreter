#include "Node.h"
#include "Interpreter.h"

Node::Node() : _value(""), _left(nullptr), _right(nullptr), _parentheses(0), _lineNumber(DEFAULT_LINE_NUMBER)
{
}

Node::Node(const std::string& value) : _value(value), _left(nullptr), _right(nullptr), _parentheses(0), _lineNumber(DEFAULT_LINE_NUMBER)
{
}

Node::Node(const std::string& value, int lineNumber) : _value(value), _left(nullptr), _right(nullptr), _parentheses(0), _lineNumber(lineNumber)
{
}

Node::~Node()
{
	// delete subtrees
	delete this->_left;
	this->_left = nullptr;
	delete this->_right;
	this->_right = nullptr;
	// check delete const
	if (this->_const && this->_const->checkDelete())
	{
		delete this->_const;
		this->_const = nullptr;
	}
}

bool Node::isLeaf()
{
	return this->_left == nullptr && this->_right == nullptr;
}

// deep copy operator
Node& Node::operator=(const Node& other)
{
	// copy values
	this->_value = other._value;
	this->_parentheses = other._parentheses;
	this->_lineNumber = other._lineNumber;
	// copy left subtree if it exists
	if (other._left != nullptr)
	{
		this->_left = new Node();
		*this->_left = *other._left;
	}
	else
	{
		this->_left = other._left;
	}
	// copy right subtree if it exists
	if (other._right != nullptr)
	{
		this->_right = new Node();
		*this->_right = *other._right;
	}
	else
	{
		this->_right = other._right;
	}
	
	return *this;
}

Node* Node::copy()
{
	// copy to new node by assignment
	Node* newCopy = new Node();
	*newCopy = *this;
	return newCopy;
}

char Node::getParentheses()
{
	return this->_parentheses;
}

void Node::setParentheses(const char c)
{
	this->_parentheses = c;
}

int Node::getLineNumber()
{
	return this->_lineNumber;
}

void Node::checkConst()
{
	this->_const = Interpreter::constValue(this->_value);
}
