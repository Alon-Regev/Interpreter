#include "Block.h"

Block::Block(Interpreter& interpreter, Node* node) : Type(BLOCK), _interpreter(interpreter)
{
	this->_code = node->copy();
	this->_code->_block = false;	// block -> executable tree
}

Block::~Block()
{
	delete this->_code;
}

Type* Block::copy()
{
	return new Block(this->_interpreter, this->_code);
}

Node* Block::getCode()
{
	return this->_code;
}

Interpreter& Block::getInterpreter()
{
	return this->_interpreter;
}

Type* Block::run(bool openScope)
{
	if(openScope)
		Interpreter::openScope();
	Type* res = this->_interpreter.value(this->_code);
	if(openScope)
		Interpreter::closeScope();
	return res;
}

std::vector<Node*> Block::split()
{
	Node* current = this->_code;
	std::vector<Node*> result;
	while (current && current->_value == ";")
	{
		result.push_back(current->_right);
		current = current->_left;
	}
	if (current)
		result.push_back(current);
	return result;
}
