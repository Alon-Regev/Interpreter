#pragma once
#include <map>
#include <string>
#include <regex>
#include "Helper.h"
#include "PreprocessorException.h"

class Type;

typedef Type* (*staticFunction)(Type*);

class Preprocessor
{
public:
	void process(std::string& code);
	const std::map<std::string, staticFunction>& getImportedFunctions();
	const std::map<std::string, Type*>& getImportedVariables();
	void importDll(const std::string& path);
private:
	void command(std::string& code, const std::string& command);

	std::map<std::string, staticFunction> _importedFunctions;
	std::map<std::string, Type*> _importedVariables;
};

