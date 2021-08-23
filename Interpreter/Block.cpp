#include "Block.h"

Block::Block(Interpreter& interpreter, Node* node, std::map<std::string, Type*>& parentVariables) : Type(BLOCK), _interpreter(interpreter)
{
	this->_code = node->copy();
	this->_code->_block = false;	// block -> executable tree
	// copy parentVariables into variables
	for (const std::pair<std::string, Type*>& pair : parentVariables)
	{
		this->_variables[pair.first] = pair.second;
		this->_parentVariables.push_back(pair.first);
	}
}

Block::~Block()
{
	delete this->_code;
	// delete variables
	/*for (const std::pair<std::string, Type*>& pair : this->_variables)
		delete pair.second;*/
}

Type* Block::copy()
{
	return new Block(this->_interpreter, this->_code, this->_variables);
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
	Type* res = this->_interpreter.value(this->_code, this->_variables);
	// delete variables
	for (auto it = this->_variables.cbegin(); it != this->_variables.cend();)
	{
		if (std::find(this->_parentVariables.begin(), this->_parentVariables.end(), it->first) == this->_parentVariables.end())
		{
			delete it->second;
			it = this->_variables.erase(it);
		}
		else
		{
			it = std::next(it);
		}
	}
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

std::map<std::string, Type*>& Block::getVariables()
{
	return this->_variables;
}
