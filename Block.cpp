#include "Block.h"

Block::Block(Interpreter& interpreter, Node* node) : Type(BLOCK), _interpreter(interpreter), _code(new Node(""))
{
	*this->_code = *node;
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

Type* Block::run()
{
	return this->_interpreter.value(this->_code);
}
