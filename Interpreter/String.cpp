#include "String.h"

String::String() : Type(STRING)
{
}
String::String(std::string content) : Type(STRING), _content(content)
{
}

std::string String::toString() const
{
    return this->_content;
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
    return new String(this->toString() + other->toString());
}

Type* String::assign(Type* other)
{
    this->_content = other->toString();
    return this;
}

Type* String::index(Type* other)
{
    int index;
    if (other->getType() == INT)
        index = ((Int*)other)->getValue();
    else if (other->getType() == LIST)
    {
        // regular index [n]
        if (((List*)other)->getContent().size() == 1 && ((List*)other)->getContent()[0]->getType() == INT)
            index = ((Int*)((List*)other)->getContent()[0])->getValue();
        else
            throw SyntaxException("Invalid index syntax");
    }
    else
        return Type::index(other);
    if (0 <= index && index < this->_content.size())
        return new Char(this->_content[index]);
    else
        throw InvalidOperationException("Index out of range");
}

Type* String::addAssign(Type* other)
{
    this->_content += other->toString();
    return this;
}

Type* String::equal(Type* other)
{
    return new Bool(this->_content == other->toString());
}

Type* String::notEqual(Type* other)
{
    return new Bool(this->_content != other->toString());
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

Type* String::toChar()
{
    if (this->_content.size() == 1)
        return new Char(this->_content[0]);
    else
        throw InvalidOperationException("casting string with length which isn't 1 to char");
    return nullptr;
}

const std::string& String::getContent()
{
    return this->_content;
}
