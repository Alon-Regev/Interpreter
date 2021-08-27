#pragma once
#include <exception>
#include <string>

#define DEFAULT_LINE_NUMBER -1

class InterpreterException : public std::exception
{
public:
    InterpreterException(const std::string& message, int lineNumber = DEFAULT_LINE_NUMBER) : 
        _message(message), _lineNumber(lineNumber)
    {
        generateMessage();
    }
    // updates full message
    void generateMessage()
    {
        if (this->_lineNumber == DEFAULT_LINE_NUMBER)
            this->_fullMessage = this->_message;    // no line number
        else    // including line numberi n message
            this->_fullMessage = "On line number " + std::to_string(_lineNumber) + '\n' + this->_message;
    }
    virtual const char* what() const override 
    { 
        return this->_fullMessage.c_str(); 
    }
    int getLineNumber() const
    {
        return this->_lineNumber;
    }
    void setLineNumber(int lineNumber)
    {
        this->_lineNumber = lineNumber;
        // update message with line number
        generateMessage();
    }
private:
    int _lineNumber;
    std::string _message;
    std::string _fullMessage;
};

