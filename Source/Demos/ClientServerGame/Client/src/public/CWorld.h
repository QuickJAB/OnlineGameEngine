#pragma once

#include <vector>

#include <core/ECS/system/DrawSys.h>

#include <GWorld.h>

struct SpriteComp;

class CWorld : public GWorld
{
public:
	CWorld();
	~CWorld();

	void update(float in_dt) override;

	std::vector<SpriteComp>* getSprites();

private:
	DrawSys* drawSys = nullptr;
};