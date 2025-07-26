#pragma once

#include <cstdint>

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