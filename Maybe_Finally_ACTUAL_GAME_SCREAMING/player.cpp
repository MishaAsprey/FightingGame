#include "Player.h"

Player::Player(int xPos, int yPos, const char * texture)
	: _xPos(xPos), _yPos(yPos), _running(false), _attack(false), _eventID(0)
{
	auto surface = IMG_Load(texture);
	_pTexture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	SDL_FreeSurface(surface);
}

Player::~Player()
{
	SDL_DestroyTexture(_pTexture);
}

//void Player::draw(int x, int character)
//{
//	if (character == 0)
//		drawKnight(x);
//	else
//		drawSamurai(x);
//}

void Player::drawKnight(int &x, int &saveEvent, int &kAnimDel)
{
	if (saveEvent != getEventID()) {
		x = 60;
		saveEvent = getEventID();
	}

	if (kAnimDel >= 5) { //animation delay for knight
		x += 180;

		int limit = 1800;
		if (isRunning())
			limit = 1440;
		else if (attack())
			limit = 1260;

		if (x >= limit) {
			x = 60; //90-21
		}
		kAnimDel = 0;
	}

	_running = false;
	int y = 45; //90 - 30 - 15

	if (_velx != 0) {
		y = 145; //160 - 15
		_running = true;
	}
	else if (_attack) {
		y = 230 + 1; //245
	}

	SDL_Rect srcrect { x, y, 70, 70 };
	SDL_Rect dstrect { _xPos, _yPos, 200, 200 };
	SDL_RenderCopyEx(Window::renderer, _pTexture, &srcrect, &dstrect, NULL, nullptr, _flip);
}

void Player::drawSamurai(int x)
{
	_running = false;
	int y = 0;

	if (_velx != 0)
		y = 195 + 1; //200
	else if (_attack)
		y = 400 + 8;

	SDL_Rect srcrect { x, y, 200, 200 };
	SDL_Rect dstrect { _xPos, _yPos + 13, 600, 600 };
	SDL_RenderCopyEx(Window::renderer, _pTexture, &srcrect, &dstrect, NULL, nullptr, _flip);
}

void Player::pollEventsP1(SDL_Event &event)
{
	const Uint8 * keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_D]) {
		_eventID = 1;
		_velx = 7;
		_flip = SDL_FLIP_NONE;
	}
	else if (keyState[SDL_SCANCODE_A]) {
		_eventID = 2;
		_velx = -7;
		_flip = SDL_FLIP_HORIZONTAL;
	}
	else if (keyState[SDL_SCANCODE_SPACE]) {
		_eventID = 3;
		_velx = 0;
		_attack = true;
	}
	else {
		_eventID = 0;
		_velx = 0;
		_attack = false;
	}

	SDL_PumpEvents();
}

void Player::pollEventsP2(SDL_Event &event)
{
	const Uint8 * keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_RIGHT]) {
		_eventID = 1;
		_velx = 7;
		_flip = SDL_FLIP_NONE;
	}
	else if (keyState[SDL_SCANCODE_LEFT]) {
		_eventID = 2;
		_velx = -7;
		_flip = SDL_FLIP_HORIZONTAL;
	}
	else if (keyState[SDL_SCANCODE_R]) {
		_eventID = 3;
		_velx = 0;
		_attack = true;
	}
	else {
		_eventID = 0;
		_velx = 0;
		_attack = false;
	}
}

void Player::move(Window &window)
{
	_xPos += _velx;
	if (_xPos >= window.getWidth() - _w || _xPos <= 0)
		_xPos -= _velx;
}