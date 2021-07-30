#pragma once
#include <vector>
#include <string>
// Include needed Interpreter dependencies Here...

#define DLLEXPORT __declspec(dllexport)
extern "C" DLLEXPORT const std::vector<std::string> functions;

// Declare your functions here...
