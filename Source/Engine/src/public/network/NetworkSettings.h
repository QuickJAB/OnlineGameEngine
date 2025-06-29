#pragma once

#include <cstdint>

namespace NetSettings
{
	// Net channels are per-peer and should be used to logically separate out data flows
	enum NetChannel
	{
		unreliable,
		reliable,
		size
	};

	constexpr uint32_t PORT = 19;

	namespace ServerSettings
	{
		constexpr uint8_t MAX_CONNECTIONS = 2;
		constexpr uint32_t IN_BANDWIDTH = 0;		// Leave 0 for uncapped
		constexpr uint32_t OUT_BANDWIDTH = 0;		// Leave 0 for uncapped
		constexpr uint32_t TICK_TIME = 0;			// Leave 0 for uncapped
	}

	namespace ClientSettings
	{
		constexpr uint8_t MAX_CONNECTIONS = 1;
		constexpr uint32_t IN_BANDWIDTH = 0;		// Leave 0 for uncapped
		constexpr uint32_t OUT_BANDWIDTH = 0;		// Leave 0 for uncapped
		constexpr uint32_t TICK_TIME = 0;			// Leave 0 for uncapped
	}
}