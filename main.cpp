#include "Interpreter.h"
#include <iostream>
#include <string>
#include <exception>

void startMessage();
std::string codeInput();

int main()
{
	startMessage();

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
		catch(InterpreterException& e)
		{
			std::cout << e.what() << std::endl;
		}
	} while (input != "quit");
}

// fuction prints start message
void startMessage()
{
	std::cout << "Welcome to <nameless interpreter> version 0.3!" << std::endl << std::endl;
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