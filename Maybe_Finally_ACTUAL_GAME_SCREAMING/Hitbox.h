#pragma once

#include <SDL.h>

#include "Window.h"
#include "Player.h"

class Hitbox
{
public:
	Hitbox(Character character, int playerID, int currXpos, int currYpos, SDL_RendererFlip flip);
	~Hitbox();

	void draw() const; //for debugging purposes

private:
	int _xPos = 0;
	int _yPos = 0;
	int _width = 0;
	int _length = 0;
	SDL_Rect _hitbox;
};