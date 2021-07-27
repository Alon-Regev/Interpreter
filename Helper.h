#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "InterpreterException.h"

class Helper
{
public:
	static void trim(std::string&);
	static std::vector<std::string> split(const std::string& str, char delimiter);
	static std::string readFile(const std::string& fileName);
	static std::string getFileExtension(const std::string& path);
private:
	static const std::string _trimmedChars;
};

