#pragma once
#include <string>

class Node
{
public:
	Node();
	Node(const std::string& value);
	Node(const std::string& value, int lineNumber);
	~Node();
	std::string _value;
	Node* _left;
	Node* _right;
	bool isLeaf();

	Node& operator=(const Node& other);
	Node* copy();

	char getParentheses();
	void setParentheses(const char c);
	int getLineNumber();
private:
	char _parentheses;
	int _lineNumber;
};

