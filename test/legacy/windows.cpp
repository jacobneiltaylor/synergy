#include "synergy.h"
#include <iostream>

using namespace taylornet::synergy;

int main()
{
	loader* loader = loader::getInstance();

	library* userlib = loader->load("User32.dll");
	library* crt = loader->load("ucrtbase.dll");

	std::string symbol = "MessageBoxA";
	unsigned int mbtype = 0x00000040L | 0x00000000L;

	userlib->call<int>(symbol, NULL, "This message box was opened through LibSynergy.\nMessageBox #1", "LibSynergy", mbtype);
	userlib->call<int>(symbol, NULL, "This message box was opened through LibSynergy.\nMessageBox #2", "LibSynergy", mbtype);

	double num = 10.9;

	std::cout << crt->call<double>("floor", num) << "\n";

	loader->unloadAll();

	std::cout << "Press ENTER to continue ...";
	std::cin.get();

	return false;
}