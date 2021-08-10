#include "String.h"

String::String() : Sequence(STRING)
{
}
String::String(std::vector<char> content) : Sequence(STRING)
{
    this->_content.assign(content.begin(), content.end());
}
String::String(std::string content) : Sequence(STRING)
{
    this->_content.assign(content.begin(), content.end());
}

std::string String::toString() const
{
    return std::string(this->_content.begin(), this->_content.end());
}

Type* String::copy()
{
    return new String(this->_content);
}

bool String::isType(const std::string& value)
{
    return value.size() >= 2 && value[0] == '"' && value.back() == '"';
}

Type* String::add(Type* other)
{
    if (other->getType() == STRING)
    {
        std::vector<char> temp = this->_content;
        temp.insert(temp.end(), ((String*)other)->_content.begin(), ((String*)other)->_content.end());
        return new String(temp);
    }
    else
        return new String(this->toString() + other->toString());
}

Type* String::toInt()
{
    return new Int(this->toString());
}

Type* String::toBool()
{
    return new Bool(this->toString());
}

Type* String::toFloat()
{
    return new Float(this->toString());
}

Type* String::toType(char value)
{
    return new String(std::string(1, value));
}
