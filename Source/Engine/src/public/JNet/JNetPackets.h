#pragma once

#include <string>

namespace JNet
{
	enum JNetPktType
	{
		RequestConnect,
		Ping,
		Pong,
		Disconnect
	};

	struct RequestConnectPkt
	{
		const JNetPktType type = RequestConnect;

		const std::string serialize();
	};

	struct PingPkt
	{
		const JNetPktType type = Ping;
		unsigned long long ullSentTime;

		const std::string serialize();
	};

	struct PongPkt
	{
		const JNetPktType type = Pong;
		unsigned long long ullSentTime;
		unsigned long long ullReceivedTime;

		const std::string serialize();
		void deserialize(std::string& i_rsRef);
	};

	struct DisconnectPkt
	{
		const JNetPktType type = Disconnect;

		const std::string serialize();
	};
}