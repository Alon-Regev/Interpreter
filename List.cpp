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

Type* List::index(Type* other)
{
	int index;
	if (other->getType() == INT)
		index = ((Int*)other)->getValue();
	else if (other->getType() == LIST)
	{
		if (((List*)other)->_content.size() == 1 && ((List*)other)->_content[0]->getType() == INT)
			index = ((Int*)((List*)other)->_content[0])->getValue();
		else
			throw SyntaxException("Invalid index syntax");
	}
	else
		return Type::index(other);
	if (0 <= index && index < this->_content.size())
		return this->_content[index];
	else
		throw InvalidOperationException("List index out of range");
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
