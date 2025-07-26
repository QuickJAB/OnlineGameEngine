#pragma once

#include <cstdint>
#include <string>

namespace JNet
{
	enum PktType
	{
		RequestConnect,
		AcceptConnect,
		Ping,
		Pong
	};

	struct ClientRequestConnectPkt
	{
		const PktType ceType = RequestConnect;
	};

	struct ServerAcceptConnectPkt
	{
		const PktType ceType = AcceptConnect;
		uint32_t uClientID = 0;

		std::string serialize()
		{
			std::string sSerialized = "";

			sSerialized += BinarySerializer::serialize<uint32_t>(uClientID);

			return sSerialized;
		}
	};

	struct ServerPingPkt
	{
		const PktType ceType = Ping;
		unsigned long long ullPingTime = 0;
	};

	struct ClientPongPkt
	{
		const PktType ceType = Pong;
		unsigned long long ullPingTime = 0;
		unsigned long long ullPongTime = 0;
	};
}