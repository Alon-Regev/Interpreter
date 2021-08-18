#pragma once
#include <vector>
#include <map>
#include <string>
// Include needed Interpreter dependencies Here...
#include "../Interpreter/Type.h"

#define DLLEXPORT __declspec(dllexport)
extern "C" DLLEXPORT const std::vector<std::string> functions;
extern "C" DLLEXPORT const std::map<std::string, Type*> variables;

// Declare your functions here...
