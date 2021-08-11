#include "List.h"

List::List() : Type(LIST)
{
}

List::List(std::vector<Type*> content) : Type(LIST), _content(content)
{
}

List::~List()
{
	for (Type*& type : this->_content)
		delete type;
}

std::string List::toString() const
{
	std::string res = "[";
	if (this->_content.size() > 0)
	{
		for (Type* item : this->_content)
			res += item->toString() + ", ";
		res.pop_back();
		res.pop_back();
	}
	return res + "]";
}

Type* List::copy()
{
	std::vector<Type*> temp;
	for (Type*& type : this->_content)
		temp.push_back(type->copy());
	return new List(temp);
}

Type* List::equal(Type* other)
{
	if (this->typeCompare(other))
	{
		if (this->_content.size() != ((List*)other)->_content.size())
			return new Bool(false);
		// if any is equal, return false
		for (int i = 0; i < this->_content.size(); i++)
			if (((Bool*)this->_content[i]->notEqual(((List*)other)->_content[i]))->getValue())
				return new Bool(false);
		return new Bool(true);
	}
	else
		return Type::equal(other);
}

Type* List::notEqual(Type* other)
{
	if (this->typeCompare(other))
	{
		if (this->_content.size() != ((List*)other)->_content.size())
			return new Bool(true);
		// if any is equal, return true
		for (int i = 0; i < this->_content.size(); i++)
			if (((Bool*)this->_content[i]->equal(((List*)other)->_content[i]))->getValue())
				return new Bool(true);
		return new Bool(false);
	}
	else
		return Type::notEqual(other);
}

const std::vector<Type*>& List::getContent()
{
	return this->_content;
}

Type* List::add(Type* other)
{
	if (other->getType() == LIST)
	{
		std::vector<Type*> temp;
		// copy this values
		for (Type*& type : this->_content)
			temp.push_back(type->copy());
		// copy other's values
		for (Type*& type : ((List*)other)->_content)
			temp.push_back(type->copy());
		return new List(temp);
	}
	else
	{
		std::vector<Type*> temp;
		// copy this values
		for (Type*& type : this->_content)
			temp.push_back(type->copy());
		// add other
		temp.push_back(other->copy());
		return new List(temp);
	}
}

Type* List::assign(Type* other)
{
	if (other->getType() == LIST)
	{
		for (Type*& type : ((List*)other)->_content)
			this->_content.push_back(type->copy());
		return this;
	}
	else
		return Type::assign(other);
}

Type* List::index(Type* other)
{
	int index;
	if (other->getType() == INT)
		index = ((Int*)other)->getValue();
	else if (other->getType() == LIST)
	{
		// regular index [n]
		if (((List*)other)->_content.size() == 1 && ((List*)other)->_content[0]->getType() == INT)
			index = ((Int*)((List*)other)->_content[0])->getValue();
		else
			throw SyntaxException("Invalid index syntax");
	}
	else
		return Type::index(other);
	if (0 <= index && index < this->_content.size())
		// return reference if this isn't temporary
		return this->isVariable() ? new Reference(this->_content[index]) : this->_content[index]->copy();
	else
		throw InvalidOperationException("Index out of range");
}

Type* List::addAssign(Type* other)
{
	if (other->getType() == LIST)
	{
		// add other's values
		for (Type*& type : ((List*)other)->_content)
			this->_content.push_back(type->copy());
		return this;
	}
	else
	{
		// add other
		this->_content.push_back(other->copy());
		return this;
	}
}
