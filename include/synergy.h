#pragma once

/*

	LibSynergy - Main header file
	Copyright 2016 Taylor Networks
	Licensed under the GNU LGPL v3.0

*/

#ifndef LIBSYNERGY_BASE

#define LIBSYNERGY_BASE

// Define export attributes for Windows platform
#ifdef _WIN32
	#define WINDOWS
	#ifdef _WINDLL
		#define LIBSYNERGY_API __declspec(dllexport) 
		#include <windows.h>
	#else
		#define LIBSYNERGY_API
	#endif
#else
	#define POSIX
	#define LIBSYNERGY_API
#endif

// Custom macro required for building this library on a POSIX platform
#ifdef _POSIXSO
	#include <dlfcn.h>
	#include <linux/limits.h>
	#include <string.h>
	#include <stdexcept>
#endif

// STL Dependancies
#include <exception>
#include <string>
#include <stack>
#include <queue>
#include <map>

// Forward class declarations
namespace taylornet
{
	namespace synergy
	{
		class loader;
		class library;
	}
}

#include "synergy/loader.h"
#include "synergy/library.h"

#endif