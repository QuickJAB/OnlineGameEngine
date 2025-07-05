#pragma once

#include <core/Engine.h>

#include <GGameInstance.h>

int main()
{
	Engine* e = new Engine(new GGameInstance());
	delete e;
	return 0;
}