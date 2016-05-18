#include "synergy.h"
#include <iostream>

using namespace taylornet::synergy;

int main()
{
	loader* loader = loader::getInstance();

	library* sdl2lib = loader->load("libSDL2-2.0.so.0");

	std::string symbol = "SDL_ShowSimpleMessageBox";
	int result = sdl2lib->call<int>(symbol, 64, "LibSynergy", "This message box was opened through LibSynergy.",  NULL);

	loader->unloadAll();

	std::cout << "Press ENTER to continue ...";
	std::cin.get();

	return false;
}