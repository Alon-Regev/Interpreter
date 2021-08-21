#include "Implementation.h"

// Add names of exported functions and variables here...
const std::vector<std::string> functions = { 
	"thread", "joinThread", "joinAllThreads", "detachThread",
	"mutex", "lock", "tryLock", "unlock",
	"conditionVariable", "wait", "notify", "notifyAll"
};
const std::map<std::string, Type*> variables = {};

// Define your functions here...

Type* thread(Type* other)
{
	std::vector<Type*> args = Interpreter::getArgs(other);
	if (args.size() == 0 || args.size() > 3)
		throw InvalidOperationException("thread function gets 1 or 2 parameters");
	// check 3rd argument
	if(args.size() == 3 && (args[2]->getType() != STRING || ((String*)args[2])->getContent() != "join" && ((String*)args[2])->getContent() != "detach"))
		throw InvalidOperationException("3rd thread argument must be either \"join\" or \"detach\"");
	// if function is valid start thread
	if (args[0]->getType() == FUNCTION || args[0]->getType() == STATIC_FUNCTION)
	{
		threadList.push_back(std::thread(functionCallThread, args[0], args.size() >= 2 ? args[1]->copy() : new Undefined(), threadList.size()));
		// join or detach if specified
		if (args.size() == 3 && ((String*)args[2])->getContent() == "join")
			threadList.back().join();
		else if (args.size() == 3 && ((String*)args[2])->getContent() == "detach")
			threadList.back().detach();
	}
	else 
		throw InvalidOperationException("Can only start a thread with a function");
	return new Int(threadList.size() - 1);
}

DLLEXPORT Type* joinThread(Type* other)
{
	if (other->getType() != INT)
		throw InvalidOperationException("joinThread expects a thread identifier");
	int identifier = ((Int*)other)->getValue();
	if (identifier >= threadList.size())
		throw InvalidOperationException("invalid thread identifier");
	if (threadList[identifier].joinable())
		threadList[identifier].join();
	else
		throw InvalidOperationException("thread can't be joined");
	return new Void();
}

DLLEXPORT Type* joinAllThreads(Type* other)
{
	if (other->getType() != UNDEFINED)
		throw InvalidOperationException("joinAllThreads has no parameters");
	// check all threads
	for (std::thread& t : threadList)
		if (t.joinable())
			t.join();
	return new Void();
}

DLLEXPORT Type* detachThread(Type* other)
{
	if (other->getType() != INT)
		throw InvalidOperationException("detachThread expects a thread identifier");
	int identifier = ((Int*)other)->getValue();
	if (identifier >= threadList.size())
		throw InvalidOperationException("invalid thread identifier");
	if (threadList[identifier].joinable())
		threadList[identifier].detach();
	else
		throw InvalidOperationException("thread can't be detached");
	return new Void();
}

DLLEXPORT Type* mutex(Type* other)
{
	if (other->getType() != UNDEFINED)
		throw InvalidOperationException("mutex has no parameters");
	mutexList.push_back(std::make_unique<std::mutex>());
	return new Int(mutexList.size() - 1);
}

DLLEXPORT Type* lock(Type* other)
{
	if (other->getType() != INT)
		throw InvalidOperationException("lock expects a mutex identifier");
	int identifier = ((Int*)other)->getValue();
	if (identifier >= mutexList.size())
		throw InvalidOperationException("invalid mutex identifier");
	mutexList[identifier]->lock();
	return new Void();
}

DLLEXPORT Type* tryLock(Type* other)
{
	if (other->getType() != INT)
		throw InvalidOperationException("lock expects a mutex identifier");
	int identifier = ((Int*)other)->getValue();
	if (identifier >= mutexList.size())
		throw InvalidOperationException("invalid mutex identifier");
	if (!mutexList[identifier]->try_lock())
		throw InvalidOperationException("locking an already locked mutex");
	return new Void();
}

DLLEXPORT Type* unlock(Type* other)
{
	if (other->getType() != INT)
		throw InvalidOperationException("lock expects a mutex identifier");
	int identifier = ((Int*)other)->getValue();
	if (identifier >= mutexList.size())
		throw InvalidOperationException("invalid mutex identifier");
	mutexList[identifier]->unlock();
	return new Void();
}

DLLEXPORT Type* conditionVariable(Type* other)
{
	if (other->getType() != UNDEFINED)
		throw InvalidOperationException("conditionVariable has no parameters");
	conditionVariableList.push_back({ std::make_unique<std::condition_variable>(), std::make_unique<std::mutex>() });
	return new Int(conditionVariableList.size() - 1);
}

DLLEXPORT Type* wait(Type* other)
{
	if (other->getType() != INT)
		throw InvalidOperationException("wait expects a condition variable identifier");
	int identifier = ((Int*)other)->getValue();
	if (identifier >= conditionVariableList.size())
		throw InvalidOperationException("invalid condition variable identifier");
	// wait for condition variable
	std::unique_lock lk(*conditionVariableList[identifier].m.get());
	conditionVariableList[identifier].cv->wait(lk);
	return new Void();
}

DLLEXPORT Type* notify(Type* other)
{
	if (other->getType() != INT)
		throw InvalidOperationException("notify expects a condition variable identifier");
	int identifier = ((Int*)other)->getValue();
	if (identifier >= conditionVariableList.size())
		throw InvalidOperationException("invalid condition variable identifier");
	// notify one
	conditionVariableList[identifier].cv->notify_one();
	return new Void();
}

DLLEXPORT Type* notifyAll(Type* other)
{
	if (other->getType() != INT)
		throw InvalidOperationException("notifyAll expects a condition variable identifier");
	int identifier = ((Int*)other)->getValue();
	if (identifier >= conditionVariableList.size())
		throw InvalidOperationException("invalid condition variable identifier");
	// notify one
	conditionVariableList[identifier].cv->notify_all();
	return new Void();
}

void functionCallThread(Type* f, Type* args, int identifier)
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
		std::cerr << "Error at thread " << identifier << ": " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Error at thread " << identifier << std::endl;
	}
}
