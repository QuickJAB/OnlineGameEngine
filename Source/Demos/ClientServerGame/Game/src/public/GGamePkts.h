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
	uint8_t uPlayerID;

	const std::string serialize();
	void deserialize(std::string& i_rsData);
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

	void buildMask(const int i_ciXDir, const int i_ciYDir, const bool i_cbShooting);
	void extractFromMask(int& o_riXDir, int& o_riYDir, bool& o_rbShooting);
	const std::string serialize();
	void deserialize(std::string& i_rsData);
};