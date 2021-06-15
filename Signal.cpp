#include "Signal.h"

Signal::Signal(const std::string& value) : Type(SIGNAL), _value(value)
{
}

std::string Signal::toString() const
{
	return this->_value;
}

Type* Signal::copy()
{
	return new Signal(this->_value);
}

const std::string& Signal::getValue()
{
	return this->_value;
}
