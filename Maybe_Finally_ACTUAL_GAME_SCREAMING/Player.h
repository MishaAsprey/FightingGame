#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Window.h"
#include "Hero.h"

class Player : public Hero
{
public:
	Player(int xPos, int yPos, const char * texture);
	~Player();

	void draw(int x, int character);

	void drawKnight(int &x, int &saveEvent, int &animDelay);
	void drawSamurai(int &x, int &saveEvent, int &animDelay);

	void pollEventsP1(SDL_Event &event);
	void pollEventsP2(SDL_Event &event);
	void move(Window &window, int character);

	inline int getXpos() const { return _xPos; }
	inline bool isRunning() const { return _running; }
	inline bool attack() const { return _attack; }
	inline int getEventID() const { return _eventID; }

private:
	int _xPos, _yPos;
	bool _running;
	bool _attack;
	int _eventID;

	SDL_RendererFlip _flip;
	SDL_Texture * _pTexture;
};