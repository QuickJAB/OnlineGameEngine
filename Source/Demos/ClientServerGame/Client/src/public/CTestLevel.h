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
	DrawSys* m_pDrawSys = nullptr;
	const uint32_t m_cuNetworkId;

	const SDL_Color m_allyColour = { 0, 0, 255, 255 };
	const SDL_Color m_enemyColour = { 255, 0, 0, 255 };

public:
	CTestLevel(const uint32_t i_uNetworkId);
	~CTestLevel();

	void update(float i_fDt) override;

	void load() override;

	std::vector<SpriteComp>* getSprites();

protected:
private:
};