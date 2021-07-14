#include "Preprocessor.h"

void Preprocessor::process(std::string& code)
{
	std::smatch match;
	std::regex regex("#(.*)\n");
	while (std::regex_search(code, match, regex))
	{
		this->command(code, match.str(1));
	}
	// delete comments
	code = std::regex_replace(code, std::regex("(//.*)|(/\\*[\\S\\s]*\\*/)"), "");
}

void Preprocessor::command(std::string& code, const std::string& command)
{
	std::vector<std::string> splitCommand = Helper::split(command, ' ');
	if (splitCommand.size() == 0)
		throw PreprocessorException("Empty preprocessor statement");

	if (splitCommand[0] == "include")
	{
		if (splitCommand.size() != 2)
			throw PreprocessorException("Invalid include syntax");
		std::string includedCode = Helper::readFile(splitCommand[1]);
		code = std::regex_replace(code, std::regex('#' + command), includedCode);
	}
	else if (splitCommand[0] == "define")
	{
		if (splitCommand.size() != 3)
			throw PreprocessorException("Invalid define syntax");
		code = std::regex_replace(code, std::regex('#' + command), "");
		code = std::regex_replace(code, std::regex(splitCommand[1]), splitCommand[2]);
	}
}
