#include "synergy.h"

using namespace taylornet::synergy;

NativeLoader* NativeLoader::inst = nullptr;

NativeLoader::NativeLoader()
{}

NativeLoader* NativeLoader::getInstance()
{
	if (NativeLoader::inst == nullptr)
	{
		NativeLoader::inst = new NativeLoader();
	}

	return NativeLoader::inst;
}

void NativeLoader::unload(NativeLibrary* lib)
{
	bool done = false;
	std::stack<NativeLibrary*> temp;

	while(!done)
	{
		NativeLibrary* candidate = lib_stack.top();
		lib_stack.pop();

		if (candidate == lib)
		{
			candidate->nativeUnload();
		}
		else
		{
			temp.push(candidate);
		}
	}
	while(temp.size() > 0)
	{
		NativeLibrary* old_candidate = temp.top();
		temp.pop();
		lib_stack.push(old_candidate);
	}
}

void NativeLoader::unloadAll()
{
	while (lib_stack.size() > 0)
	{
		NativeLibrary* lib = lib_stack.top();
		lib_stack.pop();

		lib->nativeUnload();

		delete lib;
	}
}

#ifdef WINDOWS
	#include "./natives/windows/loader_windows.cpp"
#elif defined(POSIX)
	#include "./natives/posix/loader_posix.cpp"
#endif