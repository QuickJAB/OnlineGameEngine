#pragma once

#include <vector>

#include <core/ECS/system/DrawSys.h>

#include <GTestLevel.h>

struct SpriteComp;

class CTestLevel : public GTestLevel
{
public:
	CTestLevel();
	~CTestLevel();

	void update(float in_dt) override;

	std::vector<SpriteComp>* getSprites();

private:
	DrawSys* drawSys = nullptr;
};