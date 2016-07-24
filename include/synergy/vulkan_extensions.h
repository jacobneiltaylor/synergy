#pragma once

#ifndef LIBSYNERGY_VULKAN_EXT

#define LIBSYNERGY_VULKAN_EXT

#include "synergy.h"

namespace taylornet {
	namespace synergy {

		class VulkanExtensions : public AbstractLibrary<VkInstance> {

		public:
			VulkanExtensions();
		};

	}
}

#endif