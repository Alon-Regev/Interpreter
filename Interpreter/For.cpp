#include "For.h"

For::For(Type* param) : Type(FOR)
{
	if (param->getType() == BLOCK)
	{
		std::vector<Node*> lines = ((Block*)param)->split();
		if (lines.size() != 3)
			throw SyntaxException("Invalid for loop syntax");
		this->_start = new Block(((Block*)param)->getInterpreter(), lines[2], ((Block*)param)->getParentVariables(), true);
		this->_condition = new Block(((Block*)param)->getInterpreter(), lines[1], ((Block*)param)->getParentVariables(), true);
		this->_end = new Block(((Block*)param)->getInterpreter(), lines[0], ((Block*)param)->getParentVariables(), true);
		// run start
		this->_start->run()->tryDelete();
	}
}

For::~For()
{
	delete this->_start;
	delete this->_condition;
	delete this->_end;
}

Type* For::block(Type* other)
{
	if(other->getType() != BLOCK)
		throw SyntaxException("Invalid for loop syntax");
	for (; this->runCondition(); this->_end->run()->tryDelete())
		delete ((Block*)other)->run();
	return new Undefined();
}

bool For::runCondition()
{
	Type* ret = this->_condition->run();
	if (ret->getType() != _BOOL)
		throw InvalidOperationException("For loop condition doesn't return a bool");
	bool result = ((Bool*)ret)->getValue();
	delete ret;
	return result;
}
