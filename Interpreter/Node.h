#pragma once
#include <string>

class Node
{
public:
	Node(std::string value) : _value(value), _left(nullptr), _right(nullptr), _block(0) {}
	~Node();
	std::string _value;
	Node* _left;
	Node* _right;
	bool isLeaf() { return this->_left == nullptr && this->_right == nullptr; }

	Node& operator=(const Node& other);
	Node* copy();

	char _block;
};

