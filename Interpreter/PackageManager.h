#pragma once
#include <string>
#include <iostream>

#define PORT 666
#define SERVER_IP "127.0.0.1"

enum { INSTALL = 1, UPLOAD = 2 };

typedef unsigned int SOCKET;
class PackageManager
{
public:
	static void install(const std::string& package);
	static void upload(const std::string& pacakge);
private:
	static SOCKET connectSocket();
	static void sendData(SOCKET clientSocket, char* data, unsigned length);
};

