#pragma once

#ifndef LIBSYNERGY_NATIVE_LOADER

#define LIBSYNERGY_NATIVE_LOADER

#include "synergy.h"

namespace taylornet {
	
	namespace synergy {

		class LIBSYNERGY_API NativeLoader
		{
			private:
				static NativeLoader* inst;
				std::stack<NativeLibrary*> lib_stack;

				NativeLoader();

			public:
				static NativeLoader* getInstance();

				NativeLibrary* load(std::string dlname);
				void unload(NativeLibrary* lib);
				void unloadAll();
		};

	}

}


#endif