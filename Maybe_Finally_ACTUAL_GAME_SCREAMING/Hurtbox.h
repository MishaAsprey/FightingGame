#pragma once

#include <SDL.h>

#include "Window.h"
#include "Player.h"
#include "Collider.h"

class Hurtbox : public Collider
{
public:
	Hurtbox(Character character, int playerID, int currXpos, int currYpos, SDL_RendererFlip flip);
	~Hurtbox();

	void draw(Character character, int playerXpos); //for debugging purposes

private:
	SDL_Rect _hurtbox;
};