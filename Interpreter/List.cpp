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

std::vector<Type*>& List::getContent()
{
	return this->_content;
}

void List::push(Type* other)
{
	this->_content.push_back(other);
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
	if (other->getType() != LIST)
		return Type::index(other);
	// check if list is only integers
	for (Type* type : ((List*)other)->getContent())
	{
		if (type->getType() != _INT && type->getType() != UNDEFINED)
			throw SyntaxException("Invalid index syntax");
	}
	if (((List*)other)->getContent().size() > 3)
		throw SyntaxException("Invalid index syntax");

	const std::vector<Type*>& indexList = ((List*)other)->getContent();
	if (indexList.size() == 1)
	{
		// regular index
		int index = ((Int*)indexList[0])->getValue();
		if (index < 0)
			index += this->_content.size();
		if (0 <= index && index < this->_content.size())
			return this->isVariable() ? new Reference(this->_content[index]) : this->_content[index]->copy();
		else
			throw InvalidOperationException("String index out of range");
	}
	else
	{
		int step = indexList.size() == 3 && indexList[2]->getType() != UNDEFINED ? ((Int*)indexList[2])->getValue() : 1;
		// substring
		int start = indexList[0]->getType() == UNDEFINED ? (step > 0 ? 0 : this->_content.size() - 1) : ((Int*)indexList[0])->getValue();
		int end = indexList[1]->getType() == UNDEFINED ? (step > 0 ? this->_content.size() : -1 - this->_content.size()) : ((Int*)indexList[1])->getValue();
		if (start < 0)
			start += this->_content.size();
		if (end < 0)
			end += this->_content.size();

		if (step == 0)
			throw SyntaxException("Substring step can't be zero");
		std::vector<Type*> sublist;
		for (int index = start; (step > 0 ? index < end : index > end) && 0 <= index && index < this->_content.size(); index += step)
			sublist.push_back(this->_content[index]->copy());
		return new List(sublist);
	}
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
