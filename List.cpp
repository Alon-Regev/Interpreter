#include "List.h"

List::List() : Sequence(LIST)
{
}

List::List(std::vector<Type*> content) : Sequence(LIST, content)
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
		for (int i = 0; i < this->_content.size(); i++)
			if (((Bool*)this->_content[i]->notEqual(((List*)other)->_content[i]))->getValue())
				return new Bool(false);
		return new Bool(true);
	}
	else
		return Type::equal(other);
}

Type* List::add(Type* other)
{
	if (other->getType() == LIST)
	{
		std::vector<Type*> temp;
		for (Type*& type : this->_content)
			temp.push_back(type->copy());
		for (Type*& type : ((List*)other)->_content)
			temp.push_back(type->copy());
		return new List(temp);
	}
	else
		return Type::add(other);
}

Type* List::toType(Type* value)
{
	return this->isVariable() ? new Reference(value) : value->copy();
}
