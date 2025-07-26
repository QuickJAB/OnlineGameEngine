#include "jNet/JNetPackets.h"

#include "core/Serializer.h"

const std::string JNet::RequestConnectPkt::serialize()
{
    return BinarySerializer::serialize<JNetPktType>(type);
}
