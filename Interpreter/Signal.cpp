#include "Signal.h"

Signal::Signal(short value) : Type(SIGNAL), _value(value)
{
}

std::string Signal::toString() const
{
	return std::to_string(this->_value);
}

Type* Signal::copy()
{
	return new Signal(this->_value);
}

short Signal::getValue() const
{
	return this->_value;
}
