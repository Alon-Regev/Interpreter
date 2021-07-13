#pragma once
#include <string>

class Helper
{
public:
	static void trim(std::string&);
private:
	static const std::string _trimmedChars;
};

