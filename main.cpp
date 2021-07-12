#include "Interpreter.h"
#include <iostream>
#include <string>
#include <exception>

void startMessage();

int main()
{
	startMessage();

	Interpreter interpreter;
	std::string input;
	// code loop
	do
	{
		std::cout << ">>> ";
		std::getline(std::cin, input);
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
	std::cout << "Welcome to <nameless interpreter> version 0.3!" << std::endl;
}