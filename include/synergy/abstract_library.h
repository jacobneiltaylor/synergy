#pragma once

#ifndef LIBSYNERGY_ABSTRACT_LIBRARY

#define LIBSYNERGY_ABSTRACT_LIBRARY

namespace taylornet {
	namespace synergy {

		template<typename L, typename S = void*> class LIBSYNERGY_API AbstractLibrary {
		protected:
			L lib_ptr;

			virtual S getSymbol(std::string symbol) = 0;

		public: 

			template <typename T> T call(std::string symbol)
			{
				typedef T(*symbolcall)();
				symbolcall function_ptr = (symbolcall) this->getSymbol(symbol);
				return function_ptr();
			}

			template <typename T, typename ...Args> T call(std::string symbol, Args... symbolargs)
			{
				typedef T(*symbolcall)(Args...);
				symbolcall function_ptr = (symbolcall) this->getSymbol(symbol);
				return function_ptr(symbolargs...);
			}
		};

	}
}

#endif