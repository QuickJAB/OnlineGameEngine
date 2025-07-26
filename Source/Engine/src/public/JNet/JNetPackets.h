#pragma once

#include <string>

namespace JNet
{
	enum JNetPktType
	{
		RequestConnect
	};

	struct RequestConnectPkt
	{
		const JNetPktType type = RequestConnect;

		const std::string serialize();
	};
}