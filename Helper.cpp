#include "Helper.h"

void Helper::trim(std::string& str)
{
    if (str == "")
        return;
    // remove from start
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ')
            str.erase(str.begin() + i--);
        else break;
    }
    // remove from end
    for (int i = str.size() - 1; i > 0; i--)
    {
        if (str[i] == ' ')
            str.erase(str.begin() + i);
        else break;
    }
}
