#pragma once

#include <core/Engine.h>

#include "SGameInstance.h"

int main()
{
	SGameInstance* gInst = new SGameInstance();
	Engine* e = new Engine(gInst);
	return 0;
}