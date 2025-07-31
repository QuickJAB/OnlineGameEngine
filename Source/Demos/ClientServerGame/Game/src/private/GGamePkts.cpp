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