#pragma once

#include <SDL.h>

#include "Window.h"
#include "Player.h"

class Collider
{
public:
	Collider();
	~Collider();

	void move(Player &player); //move with the player
	bool collide(int damage); //GIVE THEM INT VALUES OF POSITIONS FROM MAIN

	inline int getXpos() const { return _xPos; }
	inline int getYpos() const { return _yPos; }
	inline int getWidth() const { return _width; }
	inline int getLength() const { return _length; }

protected:
	int _xPos = 0;
	int _yPos = 0;
	int _width = 0;
	int _length = 0;
};