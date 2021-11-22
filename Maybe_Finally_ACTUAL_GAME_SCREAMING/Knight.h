#pragma once

#include "Hero.h"

class Knight : public Hero
{
public:
	Knight(int x, int y, const char * texture);
	~Knight();

	void draw(int x);
	void pollEvents(SDL_Event &event);
	void move(Window &window);

	inline int getx() { return _kPosX; }
	inline bool isRunning() { return _running; }
	inline bool attack() { return _attack; }
	inline int getEventID() { return _eventID; }

private:
	int _kPosX, _kPosY;
	bool _running;
	bool _attack;
	int _eventID;
	SDL_RendererFlip _flip = SDL_FLIP_NONE;
	SDL_Texture * _kTexture;
};