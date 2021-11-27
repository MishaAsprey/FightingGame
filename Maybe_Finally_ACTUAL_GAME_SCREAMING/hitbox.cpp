#include "Hitbox.h"

Hitbox::Hitbox(int character, int playerID)
{
	_xPos = 200;
	_yPos = 200;
	_width = 200;
	_length = 200;

	_hitbox = SDL_Rect { _xPos, _yPos, _width, _length };
}

Hitbox::~Hitbox()
{}

void Hitbox::draw() const
{
	SDL_RenderDrawRect(Window::renderer, &_hitbox);
	SDL_RenderFillRect(Window::renderer, &_hitbox);
}