#include "synergy.h"

using namespace taylornet::synergy;

loader* loader::inst = nullptr;

loader::loader()
{}

loader* loader::getInstance()
{
	if (loader::inst == nullptr)
	{
		loader::inst = new loader();
	}

	return loader::inst;
}

void loader::unload(library* lib)
{
	bool done = false;
	std::stack<library*> temp;

	while(!done)
	{
		library* candidate = lib_stack.top();
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
		library* old_candidate = temp.top();
		temp.pop();
		lib_stack.push(old_candidate);
	}
}

void loader::unloadAll()
{
	while (lib_stack.size() > 0)
	{
		library* lib = lib_stack.top();
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