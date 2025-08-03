#include "GGamePkts.h"

#include "core/Serializer.h"

const std::string GameStateUpdatePkt::serialize()
{
	std::string sData = BinarySerializer::serialize<GPktType>(type);
	return sData;
}

void GameStateUpdatePkt::deserialize(std::string& i_rsData)
{
}

void ClientInputPkt::buildMask(const float i_cfXDir, const float i_cfYDir, const bool i_cbShooting)
{
	if (i_cfXDir < 0) uInputBitMask |= 1 << 0;
	else if (i_cfXDir > 0) uInputBitMask |= 1 << 1;
	
	if (i_cfYDir < 0) uInputBitMask |= 1 << 2;
	else if (i_cfYDir > 0) uInputBitMask |= 1 << 3;
	
	if (i_cbShooting) uInputBitMask |= 1 << 4;
}

void ClientInputPkt::extractFromMask(float& o_rfXDir, float& o_rfYDir, bool& o_rbShooting)
{
	o_rfXDir = 0;
	o_rfYDir = 0;
	o_rbShooting = false;

	if (uInputBitMask & 1) o_rfXDir = -1;
	else if (uInputBitMask & 2) o_rfXDir = 1;

	if (uInputBitMask & 4) o_rfYDir = -1;
	else if (uInputBitMask & 8) o_rfYDir = 1;

	if (uInputBitMask & 16) o_rbShooting = true;
}

const std::string ClientInputPkt::serialize()
{
	std::string sData = BinarySerializer::serialize<GPktType>(type);
	sData += BinarySerializer::serialize<uint8_t>(uPlayerID);
	sData += BinarySerializer::serialize<uint8_t>(uInputBitMask);
	return sData;
}

void ClientInputPkt::deserialize(std::string& i_rsData)
{
	uPlayerID = BinarySerializer::deserialize<uint8_t>(i_rsData);
	uInputBitMask = BinarySerializer::deserialize<uint8_t>(i_rsData);
}