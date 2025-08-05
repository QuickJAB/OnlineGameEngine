#pragma once

#include <unordered_map>

namespace JNet
{
	class JNetPeer;
	struct JNetInPktData;
	enum JNetPktType;
}

class Controller;

class GameState
{
public:
protected:
	std::unordered_map<uint8_t, Controller*> m_umControllers;

	JNet::JNetPeer* const m_cpPeer;

private:

public:
	GameState(JNet::JNetPeer* const i_cpPeer);
	~GameState();

	void addController(const uint8_t i_cuConnectionId, Controller* const i_cpController);
	Controller* const getController(const uint8_t i_cuConnectionId);

protected:
private:
};