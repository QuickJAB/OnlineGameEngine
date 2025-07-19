#pragma once

#include <vector>
#include <SDL3/SDL_pixels.h>

#include <core/ECS/system/DrawSys.h>

#include <GTestLevel.h>

struct SpriteComp;

class CTestLevel : public GTestLevel
{
public:
protected:
private:
	DrawSys* const m_cpDrawSys;
	const uint32_t m_cuNetworkId;

	const SDL_Color m_cAllyColour = { 0, 0, 255, 255 };
	const SDL_Color m_cEnemyColour = { 255, 0, 0, 255 };

public:
	CTestLevel(const uint32_t i_cuNetworkId);
	~CTestLevel();

	void update(const float i_cfDt) override;

	void load() override;

	std::vector<SpriteComp>* const getSprites();

protected:
private:
};