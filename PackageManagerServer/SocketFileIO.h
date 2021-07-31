#pragma once
#include <WinSock2.h>
#include <fstream>

#define BUFFER_SIZE 4096 // 4Kb

class SocketFileIO
{
public:
	SocketFileIO(SOCKET s, const std::string& path);
	void socketToFile();
	void fileToSocket();
	int fileSize();
private:
	SOCKET _socket;
	std::string _path;
	char _buffer[BUFFER_SIZE] = { 0 };
};

