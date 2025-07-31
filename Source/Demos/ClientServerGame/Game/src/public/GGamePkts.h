#pragma once

#include <cstdint>
#include <string>

enum GPktType : uint8_t
{
	StartMatch
};

struct StartMatchPkt
{
	const GPktType type = StartMatch;
	uint8_t uPlayerID;

	const std::string serialize();
	void deserialize(std::string& i_rsData);
};