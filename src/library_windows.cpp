#include "synergy.h"

using namespace taylornet::synergy;

void* library::getNativeSymbol(const char* symbol)
{
	return (void*)GetProcAddress((HMODULE)this->lib_ptr, symbol);
}

void library::nativeUnload()
{
	FreeLibrary((HMODULE)this->lib_ptr);
}