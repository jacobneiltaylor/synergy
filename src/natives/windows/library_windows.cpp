#include "synergy.h"

using namespace taylornet::synergy;

void* NativeLibrary::getNativeSymbol(const char* symbol)
{
	return (void*)GetProcAddress((HMODULE)this->lib_ptr, symbol);
}

void NativeLibrary::nativeUnload()
{
	FreeLibrary((HMODULE)this->lib_ptr);
}