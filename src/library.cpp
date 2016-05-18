#include "synergy.h"

using namespace taylornet::synergy;

library::library(std::string name, std::string filename, void* lib_ptr)
{
	this->name = name;
	this->filename = filename;
	this->lib_ptr = lib_ptr;
}

std::string library::getName()
{
	return name;
}

std::string library::getFilename()
{
	return filename;
}