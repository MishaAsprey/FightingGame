#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Window.h"
#include "Hero.h"

enum class Character
{
	knight, samurai
};

class Player : public Hero
{
public:
	Player(int xPos, int yPos, const char * texture, SDL_RendererFlip flip, Character character, int playerID);
	~Player();

	void draw(int &x, int &saveEvent, int &animDelay);

	void drawKnight(int &x, int &saveEvent, int &animDelay);
	void drawSamurai(int &x, int &saveEvent, int &animDelay);

	void pollEventsP1(SDL_Event &event);
	void pollEventsP2(SDL_Event &event);
	void move(Window &window);
	void takeHit(Character character, int damage, Player& player);

	inline int getXpos() const { return _xPos; }
	inline int getYpos() const { return _yPos; }
	inline bool isRunning() const { return _running; }
	inline bool attack() const { return _attack; }
	inline int getEventID() const { return _eventID; }
	inline int getHealth() const { return _health; }
	inline SDL_RendererFlip getFlip() const { return _flip; }

private:
	int _xPos, _yPos;
	bool _running;
	bool _attack;
	int _eventID;
	int _playerID;

	int _health = 0;
	int _damage = 0;

	Character _character;

	SDL_RendererFlip _flip;
	SDL_Texture * _pTexture;
};