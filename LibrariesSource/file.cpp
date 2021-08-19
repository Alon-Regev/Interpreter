#include "Implementation.h"

// Add names of exported functions and variables here...
const std::vector<std::string> functions = { "fileSize", "directoryFiles", "createFile", "createDirectory" };
const std::map<std::string, Type*> variables = {
	{"file", new Class("file", std::map<std::string, Type*>
		{
			{"file", new StaticFunction((staticFunction)file)},
			{"fileObject", new Data<std::fstream>()},
			{"path", new String()},

			{"read", new StaticFunction((staticFunction)read)},
			{"readLine", new StaticFunction((staticFunction)readLine)},
			{"readLines", new StaticFunction((staticFunction)readLines)},
			{"write", new StaticFunction((staticFunction)write)},
			{"writeLine", new StaticFunction((staticFunction)writeLine)},
			{"writeLines", new StaticFunction((staticFunction)writeLines)},
			{"close", new StaticFunction((staticFunction)close)},
			{"length", new StaticFunction((staticFunction)fileLength)},
			{"getPos", new StaticFunction((staticFunction)getPos)},
			{"setPos", new StaticFunction((staticFunction)setPos)},
			{"movePos", new StaticFunction((staticFunction)movePos)},
			{"posEnd", new StaticFunction((staticFunction)posEnd)},
			{"posStart", new StaticFunction((staticFunction)posStart)},
		}
	)}
};

// Define your functions here...

Type* file(Type* other, Type* _this)
{
	if (other->getType() != STRING)
		throw InvalidOperationException("File constructor has a single string parameter");
	// extract values
	std::string path = ((String*)other)->toString();
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	// open file
	fileObject->getData().open(path);
	if (!fileObject->getData().is_open() || !fileObject->getData().good())
		throw InvalidOperationException("Can't open file");
	// save path
	((String*)((Object*)_this)->getVariables()["path"])->setContent(path);
	return new Void();
}

Type* read(Type* other, Type* _this)
{
	int readAmount = 0;
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	if (other->getType() == INT)
		readAmount = ((Int*)other)->getValue();
	else if (other->getType() == UNDEFINED)
	{	// read entire file
		int start = fileObject->getData().tellg();
		fileObject->getData().seekg(0, fileObject->getData().end);
		int end = fileObject->getData().tellg();
		readAmount = end - start;
		fileObject->getData().seekg(start);
	}
	else
		throw InvalidOperationException("Invalid arguments to read method");
	std::string buffer(readAmount, ' ');
	fileObject->getData().read(&buffer[0], readAmount);
	fileObject->getData().flush();
	fileObject->getData().clear();
	return new String(buffer);
}

Type* readLine(Type* other, Type* _this)
{
	if (other->getType() != UNDEFINED)
		throw InvalidOperationException("readline method has no parameters");
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	std::string line;
	std::getline(fileObject->getData(), line);
	fileObject->getData().flush();
	fileObject->getData().clear();
	return new String(line);
}

Type* readLines(Type* other, Type* _this)
{
	if (other->getType() != UNDEFINED)
		throw InvalidOperationException("readline method has no parameters");
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	// read file
	std::string line;
	List* result = new List();
	std::getline(fileObject->getData(), line);
	while (std::getline(fileObject->getData(), line))
		result->push(new String(line));
	fileObject->getData().flush();
	fileObject->getData().clear();
	return result;
}

Type* write(Type* other, Type* _this)
{
	if (other->getType() != STRING)
		throw InvalidOperationException("write method has 1 string parameter");
	std::string toWrite = ((String*)other)->getContent();
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	fileObject->getData().write(toWrite.c_str(), toWrite.size());
	fileObject->getData().flush();
	fileObject->getData().clear();
	return new Void();
}

Type* writeLine(Type* other, Type* _this)
{
	if (other->getType() != STRING)
		throw InvalidOperationException("writeLine method has 1 string parameter");
	std::string toWrite = ((String*)other)->getContent() + "\n";
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	fileObject->getData().write(toWrite.c_str(), toWrite.size());
	fileObject->getData().flush();
	fileObject->getData().clear();
	return new Void();
}

Type* writeLines(Type* other, Type* _this)
{
	std::vector<Type*> toWrite = Interpreter::getArgs(other, true);
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	// write to file
	for (Type* line : toWrite)
	{
		if (line->getType() != STRING)
			throw InvalidOperationException("Trying to write a non-string value to file");
		fileObject->getData().write((((String*)line)->getContent() + "\n").c_str(), toWrite.size());
	}
	fileObject->getData().flush();
	fileObject->getData().clear();
	return new Void();
}

Type* close(Type* other, Type* _this)
{
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	fileObject->getData().close();
	return new Void();
}

Type* getPos(Type* other, Type* _this)
{
	if (other->getType() != UNDEFINED)
		throw InvalidOperationException("getPos method has no parameters");
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	return new Int(fileObject->getData().tellg());
}

Type* setPos(Type* other, Type* _this)
{
	if (other->getType() != INT)
		throw InvalidOperationException("setPos method has 1 int parameter");
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	fileObject->getData().seekg(((Int*)other)->getValue());
	return new Void();
}

Type* movePos(Type* other, Type* _this)
{
	if (other->getType() != INT)
		throw InvalidOperationException("movePos method has 1 int parameter");
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	fileObject->getData().seekg(((Int*)other)->getValue(), std::ios_base::cur);
	return new Void();
}

Type* posEnd(Type* other, Type* _this)
{
	if (other->getType() != UNDEFINED)
		throw InvalidOperationException("posEnd method has no parameters");
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	fileObject->getData().seekg(0, std::ios_base::end);
	return new Void();
}

Type* posStart(Type* other, Type* _this)
{
	if (other->getType() != UNDEFINED)
		throw InvalidOperationException("posStart method has no parameters");
	Data<std::fstream>* fileObject = (Data<std::fstream>*)((Object*)_this)->getVariables()["fileObject"];
	fileObject->getData().seekg(0, std::ios_base::beg);
	return new Void();
}

int fileSize(const std::string& path)
{
	struct stat stat_buf;
	int rc = stat(path.c_str(), &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}

DLLEXPORT Type* fileSize(Type* other)
{
	if(other->getType() != STRING)
		throw InvalidOperationException("fileSize has a single string parameter");
	return new Int(fileSize(((String*)other)->toString()));
}

Type* fileLength(Type* other, Type* _this)
{
	if (other->getType() != UNDEFINED)
		throw InvalidOperationException("file length method has no parameters");
	String* path = (String*)((Object*)_this)->getVariables()["path"];
	return new Int(fileSize(path->getContent()));
}

DLLEXPORT Type* directoryFiles(Type* other)
{
	if (other->getType() != STRING)
		throw InvalidOperationException("directoryFiles has 1 string parameter");
	std::string path = ((String*)other)->getContent();
	// list files
	List* result = new List();
	for (const auto& entry : fs::directory_iterator(path))
		result->push(new String(entry.path().generic_string()));
	return result;
}

DLLEXPORT Type* createFile(Type* other)
{
	if (other->getType() != STRING)
		throw InvalidOperationException("directoryFiles has 1 string parameter");
	std::string path = ((String*)other)->getContent();
	// create file
	std::ofstream(path).close();
	return new Void();
}

DLLEXPORT Type* createDirectory(Type* other)
{
	if (other->getType() != STRING)
		throw InvalidOperationException("directoryFiles has 1 string parameter");
	std::string path = ((String*)other)->getContent();
	// create directory
	fs::create_directory(path);
	return new Void();
}
