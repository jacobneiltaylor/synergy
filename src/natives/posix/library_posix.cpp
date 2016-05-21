#include "synergy.h"

using namespace taylornet::synergy;

void* library::getNativeSymbol(const char* symbol)
{
	return dlsym(this->lib_ptr, symbol);
}

void library::nativeUnload()
{
	dlclose(this->lib_ptr);
}