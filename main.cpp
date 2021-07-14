#include "Interpreter.h"
#include "Preprocessor.h"
#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <sstream>

#define VERSION "0.3"
#define NAME "<nameless interpreter>"

std::string codeInput();
void runInterpreter();
int runFile(std::string& fileName);

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		runInterpreter();
		return 0;
	}
	std::string command(argv[1]);
	if (command == "--version")
		std::cout << NAME << " " << VERSION << std::endl;
	else if (command == "--help")
		std::cout <<
		"--help    : shows list of commands (this)\n"
		"--version : shows version number\n\n"

		"<file>    : runs a code file\n"
		"-d        : runs file in line-by-line basic debug mode\n"
		"-ad       : advanced debug mode\n";
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
		Preprocessor().process(code);
		Interpreter().run(code);
	}
	catch (InterpreterException& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}