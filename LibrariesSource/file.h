#pragma once
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
// Include needed Interpreter dependencies Here...
#include "../Interpreter/Type.h"
#include "../Interpreter/Class.h"
#include "../Interpreter/Data.h"
#include "../Interpreter/StaticFunction.h"

#define DLLEXPORT __declspec(dllexport)
extern "C" DLLEXPORT const std::vector<std::string> functions;
extern "C" DLLEXPORT const std::map<std::string, Type*> variables;

// Declare your functions here...
Type* file(Type* other, Type* _this);
Type* read(Type* other, Type* _this);
Type* readLine(Type* other, Type* _this);
Type* readLines(Type* other, Type* _this);
Type* write(Type* other, Type* _this);
Type* writeLine(Type* other, Type* _this);
Type* writeLines(Type* other, Type* _this);
Type* close(Type* other, Type* _this);
Type* getPos(Type* other, Type* _this);
Type* setPos(Type* other, Type* _this);
Type* movePos(Type* other, Type* _this);
Type* posEnd(Type* other, Type* _this);
Type* posStart(Type* other, Type* _this);

int fileSize(const std::string& path);
extern "C" DLLEXPORT Type* fileSize(Type* other);
Type* fileLength(Type* other, Type* _this);

extern "C" DLLEXPORT Type * directoryFiles(Type * other); 
extern "C" DLLEXPORT Type * createFile(Type * other);
extern "C" DLLEXPORT Type * createDirectory(Type * other);
