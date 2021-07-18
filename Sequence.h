#pragma once
#include "Type.h"
#include "Int.h"
#include "Bool.h"
#include <vector>

#include "SyntaxException.h"
#include "InvalidOperationException.h"

#define LIST "list"

template <class T>
class Sequence : public Type
{
public:
	Sequence(std::string type) : Type(type) {}
	Sequence(std::string type, std::vector<T>& content);
	// operators
	virtual Type* assign(Type* other);
	virtual Type* index(Type* other);
	// logic operators
	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
	std::vector<T> _content;
protected:
	virtual Type* toType(T value) = 0;
};

template<class T>
inline Sequence<T>::Sequence(std::string type, std::vector<T>& content) : Type(type)
{
	this->_content.assign(content.begin(), content.end());
}

template<class T>
inline Type* Sequence<T>::assign(Type* other)
{
	if (this->typeCompare(other))
	{
		this->_content.assign(((Sequence<T>*)other)->_content.begin(), ((Sequence<T>*)other)->_content.end());
		if(!other->isVariable())
			((Sequence<T>*)other)->_content.clear();
		return this;
	}
	else
		return Type::assign(other);
}

template<class T>
inline Type* Sequence<T>::index(Type* other)
{
	int index;
	if (other->getType() == INT)
		index = ((Int*)other)->getValue();
	else if (other->getType() == LIST)
	{
		if (((Sequence<Type*>*)other)->_content.size() == 1 && ((Sequence<Type*>*)other)->_content[0]->getType() == INT)
			index = ((Int*)((Sequence<Type*>*)other)->_content[0])->getValue();
		else
			throw SyntaxException("Invalid index syntax");
	}
	else
		return Type::index(other);
	if (0 <= index && index < this->_content.size())
		return this->toType(this->_content[index]);
	else
		throw InvalidOperationException("Index out of range");
}

template<class T>
inline Type* Sequence<T>::equal(Type* other)
{
	if (this->typeCompare(other))
	{
		if (this->_content.size() != ((Sequence<T>*)other)->_content.size())
			return new Bool(false);
		for (int i = 0; i < this->_content.size(); i++)
			if (this->_content[i] != ((Sequence<T>*)other)->_content[i])
				return new Bool(false);
		return new Bool(true);
	}
	else
		return Type::equal(other);
}

template<class T>
inline Type* Sequence<T>::notEqual(Type* other)
{
	if (this->typeCompare(other))
		return new Bool(!((Bool*)this->equal(other))->getValue());
	else
		return Type::notEqual(other);
}
