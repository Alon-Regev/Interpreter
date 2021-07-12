#pragma once
#include "Type.h"
#include "Int.h"
#include "Bool.h"
#include <vector>

template <class T>
class Sequence : public Type
{
public:
	Sequence(std::string type) : Type(type) {}
	Sequence(std::string type, std::vector<T>& content);
	// operators
	virtual Type* add(Type* other);
	virtual Type* assign(Type* other);
	virtual Type* index(Type* other) = 0;
	// logic operators
	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);
protected:
	std::vector<T> _content;
};

template<class T>
inline Sequence<T>::Sequence(std::string type, std::vector<T>& content) : Type(type)
{
	this->_content.assign(content.begin(), content.end());
}

template<class T>
inline Type* Sequence<T>::add(Type* other)
{
	if (this->typeCompare(other))
	{
		this->_content.insert(this->_content.end(), ((Sequence<T>*)other)->_content.begin(), ((Sequence<T>*)other)->_content.end());
		return this;
	}
	else
		return Type::add(other);
}

template<class T>
inline Type* Sequence<T>::assign(Type* other)
{
	if (this->typeCompare(other))
	{
		this->_content.assign(((Sequence<T>*)other)->_content.begin(), ((Sequence<T>*)other)->_content.end());
		return this;
	}
	else
		return Type::assign(other);
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
