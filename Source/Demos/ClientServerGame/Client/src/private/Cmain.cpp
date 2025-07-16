#pragma once

#include <core/Engine.h>

#include "CGameInstance.h"

int main()
{
	Engine* pE = new Engine(new CGameInstance());
	delete pE;
	return 0;
}