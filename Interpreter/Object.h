#pragma once
#include "Type.h"
#include "Pair.h"
#include "String.h"
#include "List.h"
#include "Undefined.h"
#include "Reference.h"
#include "Name.h"
#include <map>

#define OBJECT "object"
#define CLASS "class"

class Object : public Type
{
public:
	template<class Iterator>
	Object(Iterator begin, Iterator end);
	Object(std::map<std::string, Type*>& variables);
	Object(Pair* pair);
	Object(const std::string& type);
	Object();
	virtual ~Object();
	virtual std::string toString() const;
	virtual Type* copy();
	void toMethods();
	// operators
	virtual Type* index(Type* other);
	virtual Type* point(Type* other);
	virtual Type* assign(Type* other);
	virtual Type* extend(Type* other);
	virtual Type* extendAssign(Type* other);
	std::map<std::string, Type*> _variables;
private:
	std::string toName(Type* type, bool checkVar = true);
};

template<class Iterator>
inline Object::Object(Iterator begin, Iterator end) : Type(OBJECT)
{
	for (Iterator it = begin; it != end; it++)
	{
		this->_variables[this->toName(((Pair*)*it)->_first)] = ((Pair*)*it)->_second->copy();
		delete (*it);
	}
}
