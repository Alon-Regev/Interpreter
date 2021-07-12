#include "List.h"

List::List() : Sequence(LIST)
{
}

List::List(std::vector<Type*> content) : Sequence(LIST, content)
{
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
	return new List(this->_content);
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
		std::vector<Type*> temp = this->_content;
		temp.insert(temp.end(), ((List*)other)->_content.begin(), ((List*)other)->_content.end());
		return new List(temp);
	}
	else
		return Type::add(other);
}

Type* List::toType(Type* value)
{
	return value;
}