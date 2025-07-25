#pragma once

#include "ComponentBase.h"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_pixels.h>

struct SpriteComp : public ComponentBase
{
	SDL_FRect rect = { 0, 0, 0, 0 };
	SDL_Color colour = { 255, 255, 255, 255 };
};