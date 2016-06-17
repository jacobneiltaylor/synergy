#include "synergy.h"

using namespace taylornet::synergy;

library::library(std::string name, std::string filename, void* lib_ptr)
{
	this->name = name;
	this->filename = filename;
	this->lib_ptr = lib_ptr;
}

void* library::getSymbol(std::string symbol)
{
	if (call_cache.find(symbol) != call_cache.end())
	{
		return call_cache[symbol];
	}
	else
	{
		void* call_ptr = this->getNativeSymbol(symbol.c_str());
		this->registerSymbol(symbol, call_ptr);
		return call_ptr;
	}
}

void library::registerSymbol(std::string symbol, void* symbol_ptr)
{
	if (symbol_ptr == nullptr)
	{
		throw new std::runtime_error("Symbol not found");
	}
	else
	{
		call_cache.insert(std::pair<std::string, void*>(symbol, symbol_ptr));
	}
}

std::string library::getName()
{
	return name;
}

std::string library::getFilename()
{
	return filename;
}

#ifdef WINDOWS
	#include "./natives/windows/library_windows.cpp"
#elif defined(POSIX)
	#include "./natives/library_posix.cpp"
#endif