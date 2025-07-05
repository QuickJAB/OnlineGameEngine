#pragma once

#include "ComponentBase.h"

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_pixels.h>

struct SpriteComp : public ComponentBase
{
	SDL_FRect rect;
	SDL_Color colour;
};