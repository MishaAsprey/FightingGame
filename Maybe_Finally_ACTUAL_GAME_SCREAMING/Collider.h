#pragma once

#include <SDL.h>

#include "Window.h"
#include "Player.h"

class Collider
{
public:
	Collider();
	~Collider();

	void move(Player& player); //move with the player

protected:
	int _xPos = 0;
	int _yPos = 0;
	int _width = 0;
	int _length = 0;
};