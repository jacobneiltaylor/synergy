#pragma once

#ifndef LIBSYNERGY_LOADER

#define LIBSYNERGY_LOADER

#include "synergy.h"

namespace taylornet {
	
	namespace synergy {

		class LIBSYNERGY_API loader
		{
			private:
				static loader* inst;
				std::stack<library*> lib_stack;

				loader();

			public:
				static loader* getInstance();

				library* load(std::string dlname);
				void unload(library* lib);
				void unloadAll();
		};

	}

}


#endif