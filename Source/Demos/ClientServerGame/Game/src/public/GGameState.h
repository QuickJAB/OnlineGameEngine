#pragma once

#include <vector>

#include <jNet/GameState.h>

struct GameStateUpdatePkt;
class GProjectileController;

class GGameState : public GameState
{
public:
protected:
	std::vector<GProjectileController*> m_vProjectiles;

private:

public:
	void serializeGameState(std::string& o_rsData);

protected:
private:
};