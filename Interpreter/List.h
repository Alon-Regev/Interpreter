#pragma once
#include <vector>
#include "Type.h"
#include "Bool.h"
#include "SyntaxException.h"
#include "Reference.h"
#include "Undefined.h"

class List : public Type
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
	virtual Type* add(Type* other);
	virtual Type* assign(Type* other);
	virtual Type* index(Type* other);
	virtual Type* addAssign(Type* other);
	// logic operators
	virtual Type* equal(Type* other);
	virtual Type* notEqual(Type* other);

	std::vector<Type*>& getContent();
	void push(Type* other);
private:
	std::vector<Type*> _content;
};

template<class Iterator>
inline List::List(Iterator begin, Iterator end) : Type(LIST)
{
	for (Iterator it = begin; it != end; it++)
	{
		this->_content.push_back((*it)->copy());
		delete (*it);
	}
}
