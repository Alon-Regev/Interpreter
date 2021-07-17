#pragma once
#include "Sequence.h"
#include "SyntaxException.h"

#define LIST "list"

class List : public Sequence<Type*>
{
public:
	List();
	List(std::vector<Type*> content);
	template<class Iterator>
	List(Iterator begin, Iterator end);
	virtual ~List();
	virtual std::string toString() const;
	virtual Type* copy();
	// operators
	virtual Type* equal(Type* other);
	virtual Type* add(Type* other);
protected:
	virtual Type* toType(Type* value);
};

template<class Iterator>
inline List::List(Iterator begin, Iterator end) : Sequence(LIST)
{
	for (Iterator it = begin; it != end; it++)
		this->_content.push_back((*it)->copy());
}
