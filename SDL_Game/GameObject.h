#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include "OwnMathFuncs.h"
#include <string>
#include <iostream>
#include "Time.h"
#include "TextureManager.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


// Base class for all the objects of the game
class GameObject
{

public:
	
	OwnMathFuncs::Vector2 position = {0, 0};
	OwnMathFuncs::Vector2 velocity = {0, 0};
	
	bool isFlipped = false;

	int img_sizeX = 30;
	int img_sizeY = 30;

	int sprite_sizeX = 30;
	int sprite_sizeY = 30;

	float scale_factor = 3;

	int layer = 0;

	explicit GameObject(SDL_Renderer* renderer);
	~GameObject();

	virtual void handleEvents();
	virtual void update();
	virtual void render(float camera_pos_x, float camera_pos_y);
	void clean();

	void setTexture(SDL_Texture* texture);

protected:
	SDL_Texture * texture;
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	SDL_Renderer* renderer;
};

#endif
