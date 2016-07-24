#include "synergy.h"

using namespace taylornet::synergy;

void* NativeLibrary::getNativeSymbol(const char* symbol)
{
	return dlsym(this->lib_ptr, symbol);
}

void NativeLibrary::nativeUnload()
{
	dlclose(this->lib_ptr);
}