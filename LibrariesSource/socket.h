#pragma once
#include <vector>
#include <map>
#include <string>
// Include needed Interpreter dependencies Here...
#pragma comment (lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>

#include <fstream>
#define BUFFER_SIZE 4096
#include <thread>

#include "../Interpreter/Type.h"
#include "../Interpreter/StaticFunction.h"
#include "../Interpreter/Data.h"
#include "../Interpreter/OtherException.h"

#define DLLEXPORT __declspec(dllexport)
extern "C" DLLEXPORT const std::vector<std::string> functions;
extern "C" DLLEXPORT const std::map<std::string, Type*> variables;

// Declare your functions here...
extern "C" DLLEXPORT Type * _socket(Type * other, Type * _this);
extern "C" DLLEXPORT Type * _send(Type * other, Type * _this);
extern "C" DLLEXPORT Type * _recv(Type * other, Type * _this);
extern "C" DLLEXPORT Type * _request(Type * other, Type * _this);
extern "C" DLLEXPORT Type * _fsend(Type * other, Type * _this);
extern "C" DLLEXPORT Type * _frecv(Type * other, Type * _this);
extern "C" DLLEXPORT Type * _frequest(Type * other, Type * _this);
extern "C" DLLEXPORT Type * _sendFile(Type * other, Type * _this);
extern "C" DLLEXPORT Type * _recvFile(Type * other, Type * _this);

extern "C" DLLEXPORT Type * _close(Type * other, Type * _this);

extern "C" DLLEXPORT Type * _serverSocket(Type * other, Type * _this);
extern "C" DLLEXPORT Type * _accept(Type * other, Type * _this);
extern "C" DLLEXPORT Type * _acceptLoop(Type * other, Type * _this);

void functionCallThread(Type* f, Type* args);
