#include "Block.h"

Block::Block(Interpreter& interpreter, Node* node, std::map<std::string, Type*>& parentVariables, bool sameScope) : Type(BLOCK), _interpreter(interpreter), _sameScope(sameScope), _parentVariables(parentVariables)
{
	this->_code = node->copy();
	this->_code->setParentheses(0);	// change into regular tree
	// copy parentVariables into variables
	if(!sameScope)
		for (const std::pair<std::string, Type*>& pair : parentVariables)
			this->_variables[pair.first] = pair.second;
}

Block::~Block()
{
	delete this->_code;
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

Type* Block::run()
{
	Type* res = this->_interpreter.value(this->_code, this->_sameScope ? this->_parentVariables : this->_variables);
	// check if need to delete variables
	if (_sameScope)
		return res;
	// delete variables
	for (auto it = this->_variables.begin(); it != this->_variables.end();)
	{
		// if variable doesn't belong to parent
		if (this->_parentVariables.find(it->first) == this->_parentVariables.end())
		{
			delete it->second;
			it = this->_variables.erase(it);
		}
		else
			it = std::next(it);
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

std::map<std::string, Type*>& Block::getParentVariables()
{
	return this->_parentVariables;
}
