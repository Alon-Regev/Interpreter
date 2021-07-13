#include "Helper.h"

const std::string Helper::_trimmedChars = " \t\n";

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
