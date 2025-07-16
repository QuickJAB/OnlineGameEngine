#pragma once

#include <core/Engine.h>

#include "SGameInstance.h"

int main()
{
	Engine* pE = new Engine(new SGameInstance());
	delete pE;
	return 0;
}