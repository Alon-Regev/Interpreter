#pragma once
#include "Sequence.h"

#define LIST "list"

class List : public Sequence<Type*>
{
public:
	List();
	List(std::vector<Type*> content);
	template<class Iterator>
	List(Iterator begin, Iterator end);
	virtual std::string toString() const;
	virtual Type* copy();
	// operators
	virtual Type* index(Type* other);
	virtual Type* equal(Type* other);
};

template<class Iterator>
inline List::List(Iterator begin, Iterator end) : Sequence(LIST)
{
	this->_content.assign(begin, end);
}
