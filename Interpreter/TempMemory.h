#pragma once
#include "Type.h"
//#include "Int.h"

#define MEMORY_CELLS 3 // for a maximum of 2 temp operands and result

class Int;
class Type;
template <class T>
class TempMemory
{
public:
	static Type* set(void*);
private:
	static unsigned int _i;
	static T _memory[MEMORY_CELLS];
};

template<class T>
inline Type* TempMemory<T>::set(void* arg)
{
	_i = (_i + 1) % MEMORY_CELLS;
	_memory[_i].set(arg);
	return &_memory[_i];
}
