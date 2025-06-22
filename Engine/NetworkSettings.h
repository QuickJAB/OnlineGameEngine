#pragma once

#include <cstdint>

namespace NetSettings
{
	constexpr uint32_t PORT = 19;

	namespace Server
	{
		constexpr uint8_t MAX_CONNECTIONS = 2;
		constexpr uint32_t IN_BANDWIDTH = 0;		// Leave 0 for uncapped
		constexpr uint32_t OUT_BANDWIDTH = 0;		// Leave 0 for uncapped
		constexpr uint32_t TICK_TIME = 0;			// Leave 0 for uncapped
	}

	namespace Client
	{

	}
}