#pragma once

#include <core/Engine.h>

#include "CGameInstance.h"

int main()
{
	Engine* e = new Engine(new CGameInstance());
	delete e;
	return 0;
}