#pragma once

#ifndef LIBSYNERGY_LIBRARY

#define LIBSYNERGY_LIBRARY

#include "synergy.h"

namespace taylornet {

	namespace synergy {

		class LIBSYNERGY_API library
		{
		friend class loader;
		private:
			std::string name;
			std::string filename;

			void* lib_ptr;

			library(std::string name, std::string filename, void* ptr);
			
			void nativeUnload();
			void* getNativeSymbol(const char* symbol);

		public:
			std::string getName();
			std::string getFilename();
			
			template <typename T> T call(std::string symbol, T returntype)
			{
				typedef T(*symbolcall)();
				symbolcall function_ptr = (symbolcall) this->getNativeSymbol(symbol.c_str());
				return function_ptr();
			}

			template <typename T, typename ...Args> T call(std::string symbol, Args... symbolargs)
			{
				typedef T(*symbolcall)(Args...);
				symbolcall function_ptr = (symbolcall) this->getNativeSymbol(symbol.c_str());
				return function_ptr(symbolargs...);
			}
		};

	}
}

#endif