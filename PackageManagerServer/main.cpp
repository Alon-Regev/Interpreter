#pragma comment (lib, "ws2_32.lib")
#include <WinSock2.h>
#include <Windows.h>
#include "Server.h"

int main()
{
	try
	{
		WSADATA wsa_data = { };
		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
			throw std::exception("WSAStartup Failed");
		// run server
		Server().run(666);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		WSACleanup();
	}
}