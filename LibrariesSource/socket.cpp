#include "Implementation.h"

// Add names of exported functions and variables here...
const std::vector<std::string> functions = {};
const std::map<std::string, Type*> variables = {
	{"client", new Class("client", std::map<std::string, Type*>
		{
			{"client", new StaticFunction((staticFunction)_socket)},
			{"socketObject", new Data<SOCKET>()},

            {"recv", new StaticFunction((staticFunction)_recv)},
            {"send", new StaticFunction((staticFunction)_send)},
            {"request", new StaticFunction((staticFunction)_request)},

            {"frecv", new StaticFunction((staticFunction)_frecv)},
            {"fsend", new StaticFunction((staticFunction)_fsend)},
            {"frequest", new StaticFunction((staticFunction)_frequest)},

            {"sendFile", new StaticFunction((staticFunction)_sendFile)},
            {"recvFile", new StaticFunction((staticFunction)_recvFile)},

            {"close", new StaticFunction((staticFunction)_close)},
		}
	)},
    {"server", new Class("server", std::map<std::string, Type*>
        {
            {"server", new StaticFunction((staticFunction)_serverSocket)},
            {"socketObject", new Data<SOCKET>()},

            {"accept", new StaticFunction((staticFunction)_accept)},
            {"acceptLoop", new StaticFunction((staticFunction)_acceptLoop)},

            {"close", new StaticFunction((staticFunction)_close)},
        }
    )}
};

// Define your functions here...

DLLEXPORT Type* _socket(Type* other, Type* _this)
{
    // get arguments
    std::string serverIP;
    int port;
    std::vector<Type*> args = Interpreter::getArgs(other);
    if (args[0]->getType() == STRING)
        serverIP = ((String*)args[0])->getContent();
    else
        throw InvalidOperationException("client socket first argument should be a string");
    if (args[1]->getType() == INT)
        port = ((Int*)args[1])->getValue();
    else
        throw InvalidOperationException("client socket first argument should be a string");
    // get socketObject from this
    SOCKET& clientSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();

    // Server/receiver address
    SOCKADDR_IN serverAddr;
    // create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cerr << "Connection failed" << std::endl;
    }
    // connect to server
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());

    // Make a connection to the server with socket SendingSocket.
    int result = connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (result != 0)
    {
        throw OtherException("socket connection failed, code " + std::to_string(WSAGetLastError()));
        closesocket(clientSocket);
    }
    return new Void();
}

DLLEXPORT Type* _send(Type* other, Type* _this)
{
    if (other->getType() != STRING)
        throw OtherException("send has 1 string parameter");
    std::string toSend = ((String*)other)->getContent();
    SOCKET& clientSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();
    int sent = send(clientSocket, toSend.c_str(), toSend.size(), 0);
    if (sent == SOCKET_ERROR)
        throw OtherException("send failed, code " + std::to_string(WSAGetLastError()));
	return new Int(sent);
}

DLLEXPORT Type* _recv(Type* other, Type* _this)
{
    if (other->getType() != INT)
        throw OtherException("send has 1 int parameter");
    int recvAmount = ((Int*)other)->getValue();
    SOCKET& clientSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();
    // create and fill buffer
    std::string result(recvAmount, 0);
    int received = recv(clientSocket, &result[0], recvAmount, 0);
    if (received == SOCKET_ERROR)
        throw OtherException("recv failed, code " + std::to_string(WSAGetLastError()));
    return new String(std::string(result.begin(), result.begin() + received));
}

DLLEXPORT Type* _request(Type* other, Type* _this)
{
    std::vector<Type*> args = Interpreter::getArgs(other);
    if (args.size() != 2 || args[0]->getType() != STRING || args[1]->getType() != INT)
        throw InvalidOperationException("Invalid parameters to method request");
    std::string toSend = ((String*)args[0])->getContent();
    int recvAmount = ((Int*)args[1])->getValue();
    SOCKET& clientSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();
    // send request and get response
    int sent = send(clientSocket, toSend.c_str(), toSend.size(), 0);
    if (sent == SOCKET_ERROR)
        throw OtherException("request failed, code " + std::to_string(WSAGetLastError()));
    std::string result(recvAmount, 0);
    int received = recv(clientSocket, &result[0], recvAmount, 0);
    if (received == SOCKET_ERROR)
        throw OtherException("request failed, code " + std::to_string(WSAGetLastError()));
    return new String(std::string(result.begin(), result.begin() + received));
}

DLLEXPORT Type* _fsend(Type* other, Type* _this)
{
    // extract arguments
    std::vector<Type*> args = Interpreter::getArgs(other);
    std::vector<std::string> toSend;
    for (Type* arg : args)
    {
        if (arg->getType() != STRING)
            throw InvalidOperationException("method fsend expects only string arguments");
        toSend.push_back(((String*)arg)->getContent());
    }
    SOCKET& clientSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();
    // send string count
    uint16_t count = toSend.size();
    int ret = send(clientSocket, (char*)&count, sizeof(count), 0);
    if (ret == SOCKET_ERROR)
        throw OtherException("fsend failed, code " + std::to_string(WSAGetLastError()));
    // send strings one by one
    for (const std::string& str : toSend)
    {
        size_t size = str.size();
        // send size
        ret = send(clientSocket, (char*)&size, sizeof(size), 0);
        if (ret == SOCKET_ERROR)
            throw OtherException("fsend failed, code " + std::to_string(WSAGetLastError()));
        // send content
        int sent = 0;
        while (sent < size) // while not all data was sent
        {
            // send as much as possible
            ret = send(clientSocket, str.c_str() + sent, size - sent, 0);
            if (ret == SOCKET_ERROR)
                throw OtherException("fsend failed, code " + std::to_string(WSAGetLastError()));
            sent += ret;
        }
    }
    return new Void();
}

DLLEXPORT Type* _frecv(Type* other, Type* _this)
{
    if (other && other->getType() != UNDEFINED)
        throw InvalidOperationException("frecv method has no parameters");
    SOCKET& clientSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();
    // recv string count
    uint16_t count = 0;
    int ret = recv(clientSocket, (char*)&count, sizeof(count), 0);
    if (ret == SOCKET_ERROR)
        throw OtherException("frecv failed, code " + std::to_string(WSAGetLastError()));
    // recv strings one by one
    List* result = count == 1 ? nullptr : new List();
    for(int i = 0; i < count; i++)
    {
        // recv string size
        size_t size = 0;
        ret = recv(clientSocket, (char*)&size, sizeof(size), 0);
        if (ret == SOCKET_ERROR)
            throw OtherException("frecv failed, code " + std::to_string(WSAGetLastError()));
        // recv content
        std::string recvStr(size, 0);
        int received = 0;
        while (received < size) // while not all data was sent
        {
            // receive as much as possible
            ret = recv(clientSocket, &recvStr[received], size - received, 0);
            if (ret == SOCKET_ERROR)
                throw OtherException("frecv failed, code " + std::to_string(WSAGetLastError()));
            received += ret;
        }
        if (count == 1)
            return new String(recvStr);
        else
            result->push(new String(recvStr));
    }
    return result;
}

DLLEXPORT Type* _frequest(Type* other, Type* _this)
{
    _fsend(other, _this);
    return _frecv(nullptr, _this);
}

DLLEXPORT Type* _sendFile(Type* other, Type* _this)
{
    // get arguments
    if (other->getType() != STRING)
        throw InvalidOperationException("method sendFile has 1 string argument");
    std::string path = ((String*)other)->getContent();
    SOCKET& clientSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();
    // send count (1)
    uint16_t count = 1;
    int ret = send(clientSocket, (char*)&count, sizeof(uint16_t), 0);
    if (ret == SOCKET_ERROR)
        throw OtherException("sendFile failed, code " + std::to_string(WSAGetLastError()));

    std::ifstream file(path, std::ios_base::binary);
    // get size
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::end);
    fileSize = (size_t)file.tellg() - fileSize;
    file.seekg(0, std::ios::beg);
    // send size
    ret = send(clientSocket, (char*)&fileSize, sizeof(size_t), 0);
    if (ret == SOCKET_ERROR)
        throw OtherException("sendFile failed, code " + std::to_string(WSAGetLastError()));
    // send content
    char buffer[BUFFER_SIZE];
    if (!file.is_open())
        throw OtherException("Can't open file");
    while (fileSize > 0)	// while not all file has been read
    {
        // read from file
        int readAmount = min(fileSize, BUFFER_SIZE);
        file.read(buffer, readAmount);
        // send in socket
        ret = send(clientSocket, buffer, readAmount, 0);
        if (ret == SOCKET_ERROR)
            throw OtherException("sendFile failed, code " + std::to_string(WSAGetLastError()));
        // go back if haven't sent everything
        file.seekg(ret - readAmount, std::ios::cur);
        fileSize -= ret;
    }
    return new Void();
}

DLLEXPORT Type* _recvFile(Type* other, Type* _this)
{
    // get arguments
    if (other->getType() != STRING)
        throw InvalidOperationException("method recvFile has 1 string argument");
    std::string path = ((String*)other)->getContent();
    SOCKET& clientSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();
    // recv count (1)
    uint16_t count = 0;
    int ret = recv(clientSocket, (char*)&count, sizeof(uint16_t), 0);
    if (ret == SOCKET_ERROR)
        throw OtherException("sendFile failed, code " + std::to_string(WSAGetLastError()));
    if (count != 1)
        throw InvalidOperationException("method recvFile got more than one message at once");
    // recv size
    size_t fileSize = 0;
    ret = recv(clientSocket, (char*)&fileSize, sizeof(size_t), 0);
    if (ret == SOCKET_ERROR)
        throw OtherException("sendFile failed, code " + std::to_string(WSAGetLastError()));
    // recv content
    char buffer[BUFFER_SIZE];
    std::ofstream file(path, std::ios_base::binary);
    if (!file.is_open())
        throw OtherException("Can't open file");
    while (fileSize > 0)	// while not all file has been read
    {
        ret = recv(clientSocket, buffer, min(fileSize, BUFFER_SIZE), 0);
        if (ret == SOCKET_ERROR)
            throw OtherException("sendFile failed, code " + std::to_string(WSAGetLastError()));
        fileSize -= ret;
        // write to file from buffer
        file.write(buffer, ret);
    }
    return new Void();
}

DLLEXPORT Type* _close(Type* other, Type* _this)
{
    if (other->getType() != UNDEFINED)
        throw InvalidOperationException("method close has no parameteres");
    SOCKET& clientSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();
    closesocket(clientSocket);
}

DLLEXPORT Type* _serverSocket(Type* other, Type* _this)
{
    // get arguments
    int port;
    if (other->getType() == INT)
        port = ((Int*)other)->getValue();
    else
        throw InvalidOperationException("server has 1 int parameter");
    // get socketObject from this
    SOCKET& listeningSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();

    // Server/receiver address
    SOCKADDR_IN serverAddr;
    // create socket
    listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listeningSocket == INVALID_SOCKET)
        throw OtherException("server failed, code " + std::to_string(WSAGetLastError()));
    struct sockaddr_in serverAddress = { 0 };
    serverAddress.sin_port = htons(port);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    int result = bind(listeningSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (result == SOCKET_ERROR)
        throw OtherException("server failed, code " + std::to_string(WSAGetLastError()));
    result = listen(listeningSocket, SOMAXCONN);
    if (result == SOCKET_ERROR)
        throw OtherException("server failed, code " + std::to_string(WSAGetLastError()));
    return new Void();
}

DLLEXPORT Type* _accept(Type* other, Type* _this)
{
    if (other->getType() != UNDEFINED && other->getType() != FUNCTION && other->getType() != STATIC_FUNCTION)
        throw InvalidOperationException("accept can only get 0 or 1 parameter");
    SOCKET& listeningSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();
    // accept
    SOCKET clientSocket = accept(listeningSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET)
        throw OtherException("accept failed, code " + std::to_string(WSAGetLastError()));
    // create client object
    std::map<std::string, Type*> vars{
        {"socketObject", new Data<SOCKET>(new SOCKET(clientSocket))},

        {"recv", new StaticFunction((staticFunction)_recv)},
        {"send", new StaticFunction((staticFunction)_send)},
        {"request", new StaticFunction((staticFunction)_request)},

        {"frecv", new StaticFunction((staticFunction)_frecv)},
        {"fsend", new StaticFunction((staticFunction)_fsend)},
        {"frequest", new StaticFunction((staticFunction)_frequest)},

        {"sendFile", new StaticFunction((staticFunction)_sendFile)},
        {"recvFile", new StaticFunction((staticFunction)_recvFile)},

        {"close", new StaticFunction((staticFunction)_close)},
    };
    std::vector<std::string> instances{ "client" };

    Object* client = new Object(vars, instances);
    if(other->getType() == UNDEFINED)
        return new Object(vars, instances);
    else
    {
        // pass to new thread
        std::thread(functionCallThread, other, client).detach();
        return new Void();
    }
}

DLLEXPORT Type* _acceptLoop(Type* other, Type* _this)
{
    if (other->getType() != FUNCTION && other->getType() != STATIC_FUNCTION)
        throw InvalidOperationException("acceptLoop has 1 function parameter");
    SOCKET& listeningSocket = ((Data<SOCKET>*)((Object*)_this)->getVariables()["socketObject"])->getData();
    // accept loop
    while (true)
    {
        // accept
        SOCKET clientSocket = accept(listeningSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET)
            throw OtherException("accept failed, code " + std::to_string(WSAGetLastError()));
        // create client object
        std::map<std::string, Type*> vars{
            {"socketObject", new Data<SOCKET>(new SOCKET(clientSocket))},

            {"recv", new StaticFunction((staticFunction)_recv)},
            {"send", new StaticFunction((staticFunction)_send)},
            {"request", new StaticFunction((staticFunction)_request)},

            {"frecv", new StaticFunction((staticFunction)_frecv)},
            {"fsend", new StaticFunction((staticFunction)_fsend)},
            {"frequest", new StaticFunction((staticFunction)_frequest)},

            {"sendFile", new StaticFunction((staticFunction)_sendFile)},
            {"recvFile", new StaticFunction((staticFunction)_recvFile)},

            {"close", new StaticFunction((staticFunction)_close)},
        };
        std::vector<std::string> instances{ "client" };

        Object* client = new Object(vars, instances);

        // send client to thread
        std::thread(functionCallThread, other, client).detach();
    }
    return new Void();
}

void functionCallThread(Type* f, Type* args)
{
    try
    {
        // create a copy of the original function to prevent running the same function twice simultaneously
        Type* copy = f->copy();
        delete copy->call(args);
        delete copy;
    }
    catch (InterpreterException& e)
    {
        std::cerr << "Error at clinet thread: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Error at client thread" << std::endl;
    }
}
