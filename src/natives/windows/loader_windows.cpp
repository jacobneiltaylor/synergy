#include "synergy.h"

using namespace taylornet::synergy;

library* loader::load(std::string dlname)
{
	// Load library from Windows API's LoadLibrary and check for success
	void* dlhandle = LoadLibrary(dlname.c_str());
	
	if (dlhandle == NULL)
	{
		throw new std::runtime_error("Library not found");
	}

	// Determine library path from Windows API's GetModuleFileName
	std::string filename;
	char str[MAX_PATH+1];
	size_t len = GetModuleFileName((HMODULE)dlhandle, str, MAX_PATH);
	str[len] = '\0';
	filename = str;

	// Create new library object and add it to the stack
	library* lib = new library(dlname, filename, dlhandle);
	lib_stack.push(lib);
	return lib;
}