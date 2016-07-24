#pragma once

#ifndef LIBSYNERGY_NATIVE_LIBRARY

#define LIBSYNERGY_NATIVE_LIBRARY

#include "synergy.h"

namespace taylornet {

	namespace synergy {

		class LIBSYNERGY_API NativeLibrary : public AbstractLibrary<void*>
		{
		friend class NativeLoader;
		private:
			std::string name;
			std::string filename;
			std::map<std::string, void*> call_cache;

			NativeLibrary(std::string name, std::string filename, void* ptr);
			
			void nativeUnload();
			void* getNativeSymbol(const char* symbol);

			void* getSymbol(std::string symbol);
			void registerSymbol(std::string symbol, void* symbol_ptr);

		public:
			std::string getName();
			std::string getFilename();
		};

	}
}

#endif