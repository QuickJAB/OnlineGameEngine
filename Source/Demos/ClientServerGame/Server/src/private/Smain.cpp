#pragma once

#include <core/Engine.h>

#include "SGameInstance.h"

int main()
{
	Engine* e = new Engine(new SGameInstance());
	delete e;
	return 0;
}