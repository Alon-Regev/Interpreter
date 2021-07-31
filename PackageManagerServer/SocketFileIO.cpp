#include "SocketFileIO.h"

SocketFileIO::SocketFileIO(SOCKET s, const std::string& path) : _socket(s), _path(path)
{
}

// function reads data from socket and writes it in the file.
void SocketFileIO::socketToFile()
{
	// open output file
	std::ofstream file(this->_path, std::ofstream::binary);
	if (!file.is_open())
		throw std::exception("Can't open file");
	// read length from socket
	unsigned length;
	int result = recv(this->_socket, (char*)&length, sizeof(unsigned), 0);
	if(result == SOCKET_ERROR)
		throw std::exception("Can't read from socket");
	// read into buffer
	while (length > 0)	// more left to read
	{
		result = recv(this->_socket, this->_buffer, min(length, BUFFER_SIZE), 0);
		if (result == SOCKET_ERROR)
			throw std::exception("Can't read from socket");
		length -= result;
		// write to file from buffer
		file.write(this->_buffer, result);
	}
}

// function reads data from file and sends it in socket.
void SocketFileIO::fileToSocket()
{
	// get and send file size
	unsigned length = this->fileSize();
	if (length == -1)
		throw std::exception("File not found");
	int result = send(this->_socket, (char*)&length, sizeof(unsigned), 0);
	if (result == SOCKET_ERROR)
		throw std::exception("Can't send data");
	// send file
	std::ifstream file(this->_path, std::ifstream::binary);
	while (length > 0)	// while not all file has been read
	{
		// read from file
		int readAmount = min(length, BUFFER_SIZE);
		file.read(this->_buffer, readAmount);
		// send in socket
		result = send(this->_socket, this->_buffer, readAmount, 0);
		if (result == SOCKET_ERROR)
			throw std::exception("Can't send data");
		// go back if haven't sent everything
		file.seekg(result - readAmount, std::ios::cur);
		length -= result;
	}
}

// function returns size of file in bytes.
int SocketFileIO::fileSize()
{
	struct stat stat_buf;
	int rc = stat(this->_path.c_str(), &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}
