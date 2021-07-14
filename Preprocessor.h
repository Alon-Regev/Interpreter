#pragma once
#include <string>
#include <regex>
#include "Helper.h"
#include "PreprocessorException.h"

class Preprocessor
{
public:
	void process(std::string& code);
private:
	void command(std::string& code, const std::string& command);
};

