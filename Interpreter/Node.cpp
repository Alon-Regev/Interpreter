#include "Node.h"

Node::~Node()
{
	delete this->_left;
	this->_left = nullptr;
	delete this->_right;
	this->_right = nullptr;
}

// deep copy operator
Node& Node::operator=(const Node& other)
{
	this->_value = other._value;
	this->_block = other._block;
	if (other._left != nullptr)
	{
		this->_left = new Node("");
		*this->_left = *other._left;
	}
	else
	{
		this->_left = other._left;
	}
	if (other._right != nullptr)
	{
		this->_right = new Node("");
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
	Node* newCopy = new Node("");
	*newCopy = *this;
	return newCopy;
}
