#pragma once

#include <SDL.h>

#include "Window.h"

class Hitbox
{
public:
	Hitbox(int character, int playerID);
	~Hitbox();

	void draw() const; //for debugging purposes

private:
	int _xPos, _yPos;
	int _width, _length;
	SDL_Rect _hitbox;
};