#include "Foreach.h"

Foreach::Foreach(Type* parameters) : Type(FOREACH)
{
	if (parameters->getType() != TUPLE || ((Tuple*)parameters)->getValues().size() != 2)
		throw SyntaxException("Foreach must get 2 values");
	if (!((Tuple*)parameters)->getValues()[0]->isVariable())
		throw SyntaxException("The first value of a foreach isn't a variable");
	std::string containerType = ((Tuple*)parameters)->getValues()[1]->getType();
	if (containerType != LIST && containerType != STRING && containerType != TUPLE && containerType != OBJECT)
		throw SyntaxException("The second value of a foreach must be a list, string, tuple or object");

	this->_current = ((Tuple*)parameters)->getValues()[0];
	this->_container = ((Tuple*)parameters)->getValues()[1]->copy();
}

Foreach::~Foreach()
{
	delete this->_container;
}

Type* Foreach::block(Type* other)
{
	if (other->getType() != BLOCK)
		throw SyntaxException("Invalid foreach syntax");
	if (this->_container->getType() == LIST)
	{
		for (Type* value : ((List*)this->_container)->getContent())
		{
			Interpreter::assign(this->_current, value, ((Block*)other)->getVariables());
			delete ((Block*)other)->run();
		}
	}
	else if (this->_container->getType() == STRING)
	{
		for (char value : ((String*)this->_container)->getContent())
		{
			Type* temp = new Char(value);
			this->_current->assign(temp);
			delete ((Block*)other)->run();
			delete temp;
		}
	}
	else if (this->_container->getType() == TUPLE)
	{
		for (Type* value : *((Tuple*)this->_container))
		{
			this->_current->assign(value);
			delete ((Block*)other)->run();
		}
	}
	else if(this->_container->getType() == OBJECT)
	{
		for (const std::pair<std::string, Type*>& pair : ((Object*)this->_container)->getVariables())
		{
			Type* temp = new String(pair.first);
			this->_current->assign(temp);
			delete ((Block*)other)->run();
			delete temp;
		}
	}
	return new Undefined();
}

Type* Foreach::comprehension(Type* a, Type* b)
{
	if (a->getType() != BLOCK)
		throw SyntaxException("Invalid comprehension syntax");
	if (!(b->getType() == TUPLE && ((Tuple*)b)->getValues().size() == 2) && !(b->getType() == TEMP_SEQUENCE && ((TempSequence*)b)->getValues().size() == 2))
		throw SyntaxException("Foreach must get 2 values");
	if (!((Tuple*)b)->getValues()[0]->isVariable())
		throw SyntaxException("The first value of a foreach isn't a variable");
	std::string containerType = ((Tuple*)b)->getValues()[1]->getType();
	if (containerType != LIST && containerType != STRING && containerType != TUPLE && containerType != OBJECT)
		throw SyntaxException("The second value of a foreach must be a list, string, tuple or object");
	Type* current = a->getType() == TUPLE ? ((Tuple*)b)->getValues()[0] : ((TempSequence*)b)->getValues()[0];
	Type* container = a->getType() == TUPLE ? ((Tuple*)b)->getValues()[1] : ((TempSequence*)b)->getValues()[1];
	TempSequence* result = new TempSequence();

	if (container->getType() == LIST)
	{
		for (Type* value : ((List*)container)->getContent())
		{
			Interpreter::assign(current, value, ((Block*)a)->getVariables());
			result->sequenceExtend(((Block*)a)->run());
		}
	}
	else if (container->getType() == STRING)
	{
		for (char value : ((String*)container)->getContent())
		{
			Type* temp = new Char(value);
			current->assign(temp);
			result->sequenceExtend(((Block*)a)->run());
			delete temp;
		}
	}
	else if (container->getType() == TUPLE)
	{
		for (Type* value : *((Tuple*)container))
		{
			current->assign(value);
			result->sequenceExtend(((Block*)a)->run());
		}
	}
	else if (container->getType() == OBJECT)
	{
		for (const std::pair<std::string, Type*>& pair : ((Object*)container)->getVariables())
		{
			Type* temp = new String(pair.first);
			current->assign(temp);
			result->sequenceExtend(((Block*)a)->run());
			delete temp;
		}
	}

	return result;
}
