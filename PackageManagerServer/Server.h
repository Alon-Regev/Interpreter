#pragma once
#pragma comment (lib, "ws2_32.lib")
#include <WinSock2.h>
#include <Windows.h>
#include <thread>
#include <iostream>
#include "SocketFileIO.h"

#define LENGTH_BYTES sizeof(unsigned)
#define BUFFER_LENGTH 

enum { INSTALL = 1, UPLOAD = 2 };

class Server
{
public:
	Server();
	~Server();
	void run(int port);
	void clientConversation(SOCKET socket);
	char* readBytes(SOCKET s);
private:
	SOCKET _serverSocket;
};
