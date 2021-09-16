#pragma once
#include <string>

#define DEFAULT_LINE_NUMBER -1

class Type;
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
	Type* _const = nullptr;
	bool isLeaf();

	Node& operator=(const Node& other);
	Node* copy();

	char getParentheses();
	void setParentheses(const char c);
	int getLineNumber();

	void checkConst();
private:
	char _parentheses;
	int _lineNumber;
};

