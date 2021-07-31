#include "PackageManager.h"
#pragma comment (lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include "../PackageManagerServer/SocketFileIO.h"

void PackageManager::install(const std::string& package)
{
    SOCKET clientSocket = PackageManager::connectSocket();
    unsigned length = package.size();
    // setup data to send
    char* data = new char[package.size() + sizeof(unsigned) + 1]();
    data[0] = INSTALL;
    memcpy(data + 1, (char*)&length, sizeof(unsigned));
    package.copy(data + sizeof(unsigned) + 1, package.size());
    // send data
    PackageManager::sendData(clientSocket, data, package.size() + sizeof(unsigned) + 1);
    // recieve file
    try
    {
        SocketFileIO(clientSocket, package).socketToFile();
    }
    catch (...)
    {
        std::cerr << "File transfer failed" << std::endl;
        exit(1);
    }
}

void PackageManager::upload(const std::string& package)
{
    SOCKET clientSocket = PackageManager::connectSocket();
    unsigned length = package.size();
    // setup data to send
    char* data = new char[package.size() + sizeof(unsigned) + 1]();
    data[0] = UPLOAD;
    memcpy(data + 1, (char*)&length, sizeof(unsigned));
    package.copy(data + sizeof(unsigned) + 1, package.size());
    // send data
    PackageManager::sendData(clientSocket, data, package.size() + sizeof(unsigned) + 1);
    // recieve file
    try
    {
        SocketFileIO(clientSocket, package).fileToSocket();
    }
    catch (...)
    {
        std::cerr << "File transfer failed" << std::endl;
        exit(1);
    }
}

SOCKET PackageManager::connectSocket()
{
    WSADATA wsaData;
    SOCKET clientSocket;
    // Server/receiver address
    SOCKADDR_IN serverAddr;
    // create socket
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cerr << "Connection failed" << std::endl;
        WSACleanup();
        exit(1);
    }
    // connect to server
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Make a connection to the server with socket SendingSocket.
    int result = connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (result != 0)
    {
        std::cerr << "Connection failed" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        exit(1);
    }

    return clientSocket;
}

void PackageManager::sendData(SOCKET clientSocket, char* data, unsigned length)
{
    int result = send(clientSocket, data, length, 0);
    if (result != length)
    {
        std::cerr << "Can't send data" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        exit(1);
    }
}
