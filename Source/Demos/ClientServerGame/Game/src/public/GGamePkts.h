#pragma once

#include <cstdint>
#include <string>

#include <JNet/JNetPackets.h>

enum GPktType : uint8_t
{
	StartMatch = JNet::JNetPktType::Size + 1,
	GameStateUpdate,
	ClientInput
};

struct StartMatchPkt
{
	const GPktType type = StartMatch;
};

struct GameStateUpdatePkt
{
	const GPktType type = GameStateUpdate;

	const std::string serialize();
	void deserialize(std::string& i_rsData);
};

struct ClientInputPkt
{
	const GPktType type = ClientInput;
	uint8_t uPlayerID;
	uint8_t uInputBitMask;

	void buildMask(const float i_cfXDir, const float i_cfYDir, const bool i_cbShooting);
	void extractFromMask(float& o_rfXDir, float& o_rfYDir, bool& o_rbShooting);
	const std::string serialize();
	void deserialize(std::string& i_rsData);
};