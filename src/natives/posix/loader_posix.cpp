#include "synergy.h"

using namespace taylornet::synergy;

NativeLibrary* NativeLoader::load(std::string dlname)
{
	// Load library from libdl's dlopen and check for success
	void* dlhandle = dlopen(dlname.c_str(), RTLD_LAZY);
	
	if (dlhandle == NULL)
	{
		throw new std::runtime_error("Library not found");
	}

	// Determine library filename from libdl's dlinfo
	char str[PATH_MAX+1];
	memset(str, 0, PATH_MAX + 1);
	dlinfo(dlhandle, RTLD_DI_ORIGIN, str);
	std::string filename = str;

	// Create new library object and add it to the stack
	NativeLibrary* lib = new NativeLibrary(dlname, filename, dlhandle);
	lib_stack.push(lib);
	return lib;
}