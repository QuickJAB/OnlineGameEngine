#include "GGamePkts.h"

#include "core/Serializer.h"

const std::string StartMatchPkt::serialize()
{
	std::string sData = BinarySerializer::serialize<GPktType>(type);
	sData += BinarySerializer::serialize<uint8_t>(uPlayerID);
	return sData;
}

void StartMatchPkt::deserialize(std::string& i_rsData)
{
	uPlayerID = BinarySerializer::deserialize<uint8_t>(i_rsData);
}

const std::string GameStateUpdatePkt::serialize()
{
	std::string sData = BinarySerializer::serialize<GPktType>(type);
	return sData;
}

void StartMatchPkt::deserialize(std::string& i_rsData)
{
}

void ClientInputPkt::buildMask(const int i_ciXDir, const int i_ciYDir, const bool i_cbShooting)
{
	if (i_ciXDir < 0) uInputBitMask |= 1 << 0;
	else if (i_ciXDir > 0) uInputBitMask |= 1 << 1;
	
	if (i_ciYDir < 0) uInputBitMask |= 1 << 2;
	else if (i_ciYDir > 0) uInputBitMask |= 1 << 3;
	
	if (i_cbShooting) uInputBitMask |= 1 << 4;
}

void ClientInputPkt::extractFromMask(int& o_riXDir, int& o_riYDir, bool& o_rbShooting)
{
	o_riXDir = 0;
	o_riYDir = 0;
	o_rbShooting = false;

	if (uInputBitMask & 1) o_riXDir = -1;
	else if (uInputBitMask & 2) o_riXDir = 1;

	if (uInputBitMask & 4) o_riYDir = -1;
	else if (uInputBitMask & 8) o_riYDir = 1;

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