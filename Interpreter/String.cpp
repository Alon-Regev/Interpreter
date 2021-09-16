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
    if (other->getType() != LIST)
        return Type::index(other);
    // check if list is only integers
    for (Type* type : ((List*)other)->getContent())
    {
        if (type->getType() != _INT && type->getType() != UNDEFINED)
            throw SyntaxException("Invalid index syntax");
    }
    if (((List*)other)->getContent().size() > 3)
        throw SyntaxException("Invalid index syntax");

    const std::vector<Type*>& indexList = ((List*)other)->getContent();
    if (indexList.size() == 1)
    {
        // regular index
        int index = ((Int*)indexList[0])->getValue();
        if (index < 0)
            index += this->_content.size();
        if (0 <= index && index < this->_content.size())
            return new Char(this->_content[index]);
        else
            throw InvalidOperationException("String index out of range");
    }
    else
    {
        int step = indexList.size() == 3 && indexList[2]->getType() != UNDEFINED ? ((Int*)indexList[2])->getValue() : 1;
        // substring
        int start = indexList[0]->getType() == UNDEFINED ? (step > 0 ? 0 : this->_content.size() - 1) : ((Int*)indexList[0])->getValue();
        int end = indexList[1]->getType() == UNDEFINED ? (step > 0 ? this->_content.size() : -1 - this->_content.size()) : ((Int*)indexList[1])->getValue();
        if (start < 0)
            start += this->_content.size();
        if (end < 0)
            end += this->_content.size();
        
        if (step == 0)
            throw SyntaxException("Substring step can't be zero");
        std::string substring = "";
        for (int index = start; (step > 0 ? index < end : index > end) && 0 <= index && index < this->_content.size(); index += step)
            substring += this->_content[index];
        return new String(substring);
    }
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

void String::setContent(const std::string& content)
{
    this->_content = content;
}
