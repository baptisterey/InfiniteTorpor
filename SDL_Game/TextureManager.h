#pragma once
#include "SDL.h"
#include "SDL_image.h"

class TextureManager
{
public:

	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer, int &w, int &h);

	static void DrawTexture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect srcrect, SDL_Rect destrect, SDL_RendererFlip render_flip = SDL_FLIP_NONE);
};

