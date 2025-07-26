#include "JNet/JNetServer.h"

JNet::JNetServer::JNetServer()
{
	JNet::init();
}

JNet::JNetServer::~JNetServer()
{
	JNet::cleanup();
}
