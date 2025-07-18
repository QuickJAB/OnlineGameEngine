#pragma once

#include <vector>

#include <core/ECS/system/DrawSys.h>

#include <GTestLevel.h>

struct SpriteComp;

class CTestLevel : public GTestLevel
{
public:
protected:
private:
	DrawSys* m_pDrawSys = nullptr;

public:
	CTestLevel();
	~CTestLevel();

	void update(float i_fDt) override;

	void load() override;

	std::vector<SpriteComp>* getSprites();

protected:
private:
};