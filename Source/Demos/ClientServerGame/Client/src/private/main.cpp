#pragma once

#include <core/Engine.h>

#include "CGameInstance.h"

int main()
{
	CGameInstance* gInst = new CGameInstance();
	Engine* e = new Engine(gInst);
	return 0;
}