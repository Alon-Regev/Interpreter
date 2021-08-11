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

#define VERSION "0.8"
#define NAME "<nameless interpreter>"

std::string codeInput();
void runInterpreter();
int runFile(std::string& fileName);

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	if (argc == 1)
	{
		runInterpreter();
		return 0;
	}
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
void runInterpreter()
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
		// process input
		try
		{
			std::string returnString = interpreter.run(input);
			std::cout << returnString << std::endl;
		}
		catch (InterpreterException& e)
		{
			std::cout << e.what() << std::endl;
		}
	} while (input != "quit");
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
		i.run(code);
	}
	catch (InterpreterException& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}