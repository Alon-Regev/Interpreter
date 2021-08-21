#include "Interpreter.h"
#include "Preprocessor.h"
#include "PackageManager.h"
#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <sstream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define VERSION "0.9"
#define NAME "<nameless interpreter>"

std::string codeInput();
int runInterpreter();
int runFile(std::string& fileName);

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	srand(time(NULL));

	if (argc == 1)
		return runInterpreter();
	std::string command(argv[1]);
	if (command == "--help")
		std::cout <<
		"--help         : shows list of commands (this)\n"
		"--version / -v : shows version number\n\n"

		"--install      : installs all projects packages\n"
		"--install <p>  : installs specified package\n"
		"--upload <p>   : uploads specified package\n\n"

		"<file>         : runs a code file\n";
	else if(command == "--version" || command == "-v")
		std::cout << NAME << " " << VERSION << std::endl;
	else if (command == "--install")
	{
		if (argc == 2)
		{
			// todo
		}
		else if(argc > 2)
		{
			for (int p = 2; p < argc; p++)
				PackageManager::install(argv[p]);
		}
	}
	else if (command == "--upload")
	{
		if (argc == 3)
		{
			PackageManager::upload(argv[2]);
		}
		else
			std::cerr << "Invalid number of arguments..." << std::endl;
	}
	else if (command.front() == '-')
	{
		std::cout << "invalid command. use --help to get list of commands." << std::endl;
		return 1;
	}
	else
		return runFile(command);
	return 0;
}

// function gets code input, spanning multiple lines if there's ';' on the end (expecting another line)
std::string codeInput()
{
	std::string input, temp;
	// get first lines
	std::cout << ">>> ";
	std::getline(std::cin, input);
	// get additional line until there is no statement connector ';' || '\'
	while (!input.empty() && (input.back() == ';' || input.back() == '\\'))
	{
		if (input.back() == '\\')
			input.pop_back();
		std::cout << "... ";
		std::getline(std::cin, temp);
		input += '\n' + temp;
	}
	return input;
}

// accepts code input from user and runs it
int runInterpreter()
{
	std::cout << "Welcome to " << NAME << " version " << VERSION << "!" << std::endl << std::endl;

	Interpreter interpreter;
	std::string input;
	// code loop
	do
	{
		input = codeInput();
		// special input
		if (input.empty() || input == "quit")
			continue;
		if (input == "clear")
		{
			system("cls");
			continue;
		}
		else if (input == "list variables" || input == "var list")
		{
			interpreter.printVariables();
			continue;
		}
		// process input
		try
		{
			// preprocess
			Preprocessor p;
			p.process(input);
			interpreter.importFunctions(p.getImportedFunctions());
			interpreter.importVariables(p.getImportedVariables());
			if (input.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
				continue;
			// run
			std::string returnString = interpreter.run(input);
			std::cout << returnString << std::endl;
		}
		catch (InterpreterException& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (ReturnException& e) 
		{
			Type* retType = e.getValue();
			int retValue = retType->getType() == INT ? ((Int*)retType)->getValue() : 0;
			delete retType;
			return retValue;
		}
	} while (input != "quit");
	return 0;
}

// function runs code file
int runFile(std::string& fileName)
{
	try
	{
		std::string code = Helper::readFile(fileName);
		Preprocessor p;
		p.process(code);
		Interpreter i;
		i.importFunctions(p.getImportedFunctions());
		i.importVariables(p.getImportedVariables());
		i.run(code);
	}
	catch (InterpreterException& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	catch (ReturnException& e)
	{
		Type* retType = e.getValue();
		int retValue = retType->getType() == INT ? ((Int*)retType)->getValue() : 0;
		delete retType;
		return retValue;
	}
}