#include "Helper.h"

const std::string Helper::_trimmedChars = " \t\r\n";

void Helper::trim(std::string& str)
{
    if (str == "")
        return;
    // remove from start
    for (int i = 0; i < str.size(); i++)
    {
        if (Helper::_trimmedChars.find(str[i]) != std::string::npos)
            str.erase(str.begin() + i--);
        else break;
    }
    // remove from end
    for (int i = str.size() - 1; i > 0; i--)
    {
        if (Helper::_trimmedChars.find(str[i]) != std::string::npos)
            str.erase(str.begin() + i);
        else break;
    }
}

std::vector<std::string> Helper::split(const std::string& str, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream sstream(str);
    std::string temp;
    while (std::getline(sstream, temp, delimiter))
        result.push_back(temp);
    return result;
}

std::string Helper::readFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
        throw InterpreterException("Can't open file \"" + fileName + '"');
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string Helper::getFileExtension(const std::string& path)
{
    size_t dotPos = path.find_last_of(".");
    if (dotPos == std::string::npos)
        return "";
    return path.substr(dotPos + 1);
}
