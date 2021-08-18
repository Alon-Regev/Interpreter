#include "Preprocessor.h"
#include <Windows.h>

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

const std::map<std::string, staticFunction>& Preprocessor::getImportedFunctions()
{
	return this->_importedFunctions;
}

const std::map<std::string, Type*>& Preprocessor::getImportedVariables()
{
	return this->_importedVariables;
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
		std::string extension = Helper::getFileExtension(splitCommand[1]);
		if (extension == "dll")
		{
			this->importDll(splitCommand[1]);
			code = std::regex_replace(code, std::regex('#' + command), "");
		}
		else if (extension == "nli")
		{
			std::string includedCode = Helper::readFile(splitCommand[1]);
			code = std::regex_replace(code, std::regex('#' + command), includedCode);
		}
		else
			throw PreprocessorException("Invalid include file extension " + (extension == "" ? "" : "." + extension));
	}
	else if (splitCommand[0] == "define")
	{
		if (splitCommand.size() != 3)
			throw PreprocessorException("Invalid define syntax");
		code = std::regex_replace(code, std::regex('#' + command), "");
		code = std::regex_replace(code, std::regex(splitCommand[1]), splitCommand[2]);
	}
}

void Preprocessor::importDll(const std::string& path)
{
	// load dll
	HINSTANCE library = LoadLibraryA(path.c_str());
	if (!library)
		throw PreprocessorException("Can't load dll " + path);

	// get list of functions
	const std::vector<std::string>* functions = (const std::vector<std::string>*)GetProcAddress(library, "functions");
	if (!functions)
		throw PreprocessorException("Included dll " + path + " has an invalid functions list");
	const std::map<std::string, Type*>* variables = (const std::map<std::string, Type*>*)GetProcAddress(library, "variables");
	if (!variables)
		throw PreprocessorException("Included dll " + path + " has an invalid variable list");
	this->_importedVariables = *variables;

	for (const std::string& function : *functions)
	{
		staticFunction pf = (staticFunction)GetProcAddress(library, function.c_str());
		if (!pf)
			throw PreprocessorException("Function " + function + " from dll " + path);
		this->_importedFunctions[function] = pf;
	}
}
