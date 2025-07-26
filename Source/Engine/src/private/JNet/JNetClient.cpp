#include "JNet/JNetClient.h"

JNet::JNetClient::JNetClient()
{
	JNet::init();
}

JNet::JNetClient::~JNetClient()
{
	JNet::cleanup();
}
