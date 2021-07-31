#include "Server.h"

// constructor and destructor
Server::Server()
{
	// open tcp listening socket
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket == INVALID_SOCKET)
	{
		throw std::exception("Error on server socket creation");
	}
}
Server::~Server()
{
	// close socket
	try
	{
		closesocket(this->_serverSocket);
	}
	catch (...) {}
}

// function accepts new clients and starts a conversation with them
void Server::run(int port)
{
	SOCKET clientSocket = { 0 };
	// set up listening socket
	struct sockaddr_in serverAddress = { 0 };
	serverAddress.sin_port = htons(port);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	// bind and listen
	if (bind(this->_serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		throw std::exception("Error on server socket bind");
	if (listen(this->_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception("Error on server socket listen");

	std::cout << "Listening on port " << port << std::endl;

	// accept new clients
	while (true)
	{
		clientSocket = accept(this->_serverSocket, NULL, NULL);
		// check socket
		if (clientSocket == INVALID_SOCKET)
			std::cerr << "server accepted an invalid socket" << std::endl;
		else	// start conversation
			std::thread(&Server::clientConversation, this, clientSocket).detach();
	}
}

// function handles conversation with a client
void Server::clientConversation(SOCKET clientSocket)
{
	char* buffer;
	// read request
	byte code = { 0 };
	int result = recv(clientSocket, (char*)&code, sizeof byte, 0);
	if (result == INVALID_SOCKET) return;
	// do action
	switch (code)
	{
	case INSTALL:
	{
		char* path = nullptr;
		try
		{
			path = this->readBytes(clientSocket);
			SocketFileIO(clientSocket, path).fileToSocket();
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		delete path;
		break;
	}
	case UPLOAD:
	{
		char* path = nullptr;
		try
		{
			path = this->readBytes(clientSocket);
			SocketFileIO(clientSocket, path).socketToFile();
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		delete path;
		break;
	}
	default:
		break;
	}
	// end conversation
	closesocket(clientSocket);
}

// function reads <n> bytes from socket
char* Server::readBytes(SOCKET s)
{
	// read length
	unsigned length;
	int result = recv(s, (char*)&length, LENGTH_BYTES, 0);
	if (result == SOCKET_ERROR) throw std::exception("Data not received");
	// read data
	char* buffer = new char[length + 1]();
	result = recv(s, buffer, length, 0);
	return buffer;
}
