#pragma once
#include <vector>
#include <map>
#include <string>
#include <regex>
// Include needed Interpreter dependencies Here...
#include "../Interpreter/Interpreter.h"
#include "../Interpreter/Type.h"

#define DLLEXPORT __declspec(dllexport)
extern "C" DLLEXPORT const std::vector<std::string> functions;
extern "C" DLLEXPORT const std::map<std::string, Type*> variables;

// Declare your functions here...
extern "C" DLLEXPORT Type * match(Type * other);
extern "C" DLLEXPORT Type * search(Type * other);
extern "C" DLLEXPORT Type * replace(Type * other);
extern "C" DLLEXPORT Type * findAll(Type * other);
