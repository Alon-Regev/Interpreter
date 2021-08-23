#pragma once
#include "Type.h"

#define DATA "data"

template<class T>
class Data : public Type
{
public:
	Data();
	Data(T* data);
	Data(T& data);
	~Data();
	virtual std::string toString() const;
	virtual Type* copy();
	static bool isType(const std::string& value) { return false; }
	T& getData();
private:
	bool _copied = false;
	T* _data;
};

template<class T>
inline Data<T>::Data() : Type(DATA), _data(new T)
{
}

template<class T>
inline Data<T>::Data(T* data) : Type(DATA), _data(data)
{
}

template<class T>
inline Data<T>::Data(T& data) : Type(DATA), _data(&data)
{
}

template<class T>
inline Data<T>::~Data()
{
	if (!this->_copied)
		delete this->_data;
}

template<class T>
inline std::string Data<T>::toString() const
{
	return DATA;
}

template<class T>
inline Type* Data<T>::copy()
{
	this->_copied = true;
	return new Data(this->_data);
}

template<class T>
inline T& Data<T>::getData()
{
	return *this->_data;
}
