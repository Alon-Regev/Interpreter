#pragma once
#include <vector>
#include <map>
#include <string>
#include <thread>
#include <mutex>
// Include needed Interpreter dependencies Here...
#include "../Interpreter/Type.h"
#include "../Interpreter/Function.h"

#define DLLEXPORT __declspec(dllexport)
extern "C" DLLEXPORT const std::vector<std::string> functions;
extern "C" DLLEXPORT const std::map<std::string, Type*> variables;

// Declare your functions here...
struct ConditionVariable
{
	std::unique_ptr<std::condition_variable> cv;
	std::unique_ptr <std::mutex> m;
};

extern "C" DLLEXPORT std::vector<std::thread> threadList = {};
extern "C" DLLEXPORT std::vector<std::unique_ptr<std::mutex>> mutexList = {};
extern "C" DLLEXPORT std::vector<ConditionVariable> conditionVariableList = {};

extern "C" DLLEXPORT Type * thread(Type * other);
extern "C" DLLEXPORT Type * joinThread(Type * other);
extern "C" DLLEXPORT Type * joinAllThreads(Type * other);
extern "C" DLLEXPORT Type * detachThread(Type * other);

extern "C" DLLEXPORT Type * mutex(Type * other);
extern "C" DLLEXPORT Type * lock(Type * other);
extern "C" DLLEXPORT Type * tryLock(Type * other);
extern "C" DLLEXPORT Type * unlock(Type * other);

extern "C" DLLEXPORT Type * conditionVariable(Type * other);
extern "C" DLLEXPORT Type * wait(Type * other);
extern "C" DLLEXPORT Type * notify(Type * other);
extern "C" DLLEXPORT Type * notifyAll(Type * other);

void functionCallThread(Type* f, Type* args, int id);
