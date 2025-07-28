#include "jNet/JNetPackets.h"

#include "core/Serializer.h"

const std::string JNet::RequestConnectPkt::serialize()
{
    return BinarySerializer::serialize<JNetPktType>(type);
}

const std::string JNet::ConnectedPkt::serialize()
{
    return BinarySerializer::serialize<JNetPktType>(type);
}

const std::string JNet::PingPkt::serialize()
{
    std::string sSerialized = BinarySerializer::serialize<JNetPktType>(type);
    sSerialized += BinarySerializer::serialize<unsigned long long>(ullSentTime);
    return sSerialized;
}

const std::string JNet::PongPkt::serialize()
{
    std::string sSerialized = BinarySerializer::serialize<JNetPktType>(type);
    sSerialized += BinarySerializer::serialize<unsigned long long>(ullSentTime);
    sSerialized += BinarySerializer::serialize<unsigned long long>(ullReceivedTime);
    return sSerialized;
}

void JNet::PongPkt::deserialize(std::string& i_rsData)
{
    ullSentTime = BinarySerializer::deserialize<unsigned long long>(i_rsData);
    ullReceivedTime = BinarySerializer::deserialize<unsigned long long>(i_rsData);
}

const std::string JNet::DisconnectPkt::serialize()
{
    return BinarySerializer::serialize<JNetPktType>(type);
}