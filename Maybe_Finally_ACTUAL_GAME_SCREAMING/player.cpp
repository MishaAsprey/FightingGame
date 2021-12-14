#include "Player.h"

Player::Player(int xPos, int yPos, const char * texture, SDL_RendererFlip flip, Character character, int playerID)
	: _xPos(xPos), _yPos(yPos), _running(false), _attack(false), _eventID(Event::idle),
	  _flip(flip), _character(character), _playerID(playerID), _size(1)
{
	switch (character) {
	case Character::knight:
		_health = 100;
		_damage = 40;
		break;
	case Character::samurai:
		_health = 70;
		_damage = 30;
		break;
	case Character::huntress:
		_health = 80;
		_damage = 40;
		break;
	default: break;
	}

	auto surface = IMG_Load(texture);
	_pTexture = SDL_CreateTextureFromSurface(Window::renderer, surface);
	SDL_FreeSurface(surface);
}

Player::~Player()
{
	SDL_DestroyTexture(_pTexture);
}

void Player::draw(int &x, Event &saveEvent, int &animDelay)
{
	if (_character == Character::knight)
		drawKnight(x, saveEvent, animDelay);
	else if (_character == Character::samurai)
		drawSamurai(x, saveEvent, animDelay);
	else if (_character == Character::huntress)
		drawHuntress(x, saveEvent, animDelay);
}

void Player::drawKnight(int &x, Event &saveEvent, int &animDelay)
{
	if (saveEvent != getEventID()) {
		x = 60;
		saveEvent = getEventID();
	}

	if (animDelay >= 5) { //animation delay for Knight
		x += 180;

		int limit = 1800;
		if (isRunning())
			limit = 1440;
		else if (attack())
			limit = 1260;

		if (x >= limit) {
			x = 60; //90-21
		}
		animDelay = 0;
	}

	animDelay++;

	_running = false;
	int y = 45; //90 - 30 - 15

	if (_velx != 0) {
		y = 145; //160 - 15
		_running = true;
	}
	else if (_attack) {
		y = 230 + 1; //245
	}
	if (_eventID == Event::attack && x >= 1100) {
		_attack = false; ///////////////////////////////
		_eventID = Event::idle;
	}

	SDL_Rect srcrect { x, y, 70, 70 };
	SDL_Rect dstrect { _xPos, _yPos, 200 * _size, 200 * _size };
	SDL_RenderCopyEx(Window::renderer, _pTexture, &srcrect, &dstrect, NULL, nullptr, _flip);
}

void Player::drawSamurai(int &x, Event &saveEvent, int &animDelay)
{
	int initial = 0; //initial x position for the Samurai sprite

	if (saveEvent != getEventID()) {
		x = initial;
		saveEvent = getEventID();
	}

	if (animDelay >= 8) { //animation delay for Samurai
		x += 200;

		int limit = 800;
		if (isRunning())
			limit = 1600;
		else if (attack())
			limit = 800;

		if (x >= limit) {
			x = initial; //90-21
		}
		animDelay = 0;
	}

	animDelay++;

	_running = false;
	int y = 0;

	if (_velx != 0)
		y = 195 + 1; //200
	else if (_attack)
		y = 400 + 8;

	if (_eventID == Event::attack && x >= 600) {
		_attack = false; ///////////////////////////////
		_eventID = Event::idle;
	}

	SDL_Rect srcrect { x, y, 200, 200 };
	SDL_Rect dstrect { _xPos, _yPos + 13, 600 * _size, 600 * _size };
	SDL_RenderCopyEx(Window::renderer, _pTexture, &srcrect, &dstrect, NULL, nullptr, _flip);
}

void Player::drawHuntress(int &x, Event &saveEvent, int &animDelay)
{
	int initial = 0; //initial x position for the Samurai sprite

	if (saveEvent != getEventID()) {
		x = initial;
		saveEvent = getEventID();
	}

	if (animDelay >= 6) { //animation delay for Samurai
		x += 150;

		int limit = 1200;
		if (isRunning())
			limit = 1200;
		else if (attack())
			limit = 750;

		if (x >= limit) {
			x = initial; //90-21
		}
		animDelay = 0;
	}

	animDelay++;

	_running = false;
	int y = 0;

	if (_velx != 0)
		y = 150 - 4; //200
	else if (_attack)
		y = 300;

	if (_eventID == Event::attack && x >= 600) {
		_attack = false; ///////////////////////////////
		_eventID = Event::idle;
	}

	SDL_Rect srcrect{ x, y, 150, 150 };
	SDL_Rect dstrect{ _xPos, _yPos + 9, 600 * _size, 600 * _size };
	SDL_RenderCopyEx(Window::renderer, _pTexture, &srcrect, &dstrect, NULL, nullptr, _flip);
}

void Player::pollEventsP1(SDL_Event &event)
{
	//switch (event.type) {
	//case SDL_KEYDOWN:
	//	switch (event.key.keysym.sym) {
	//	case SDLK_SPACE:
	//		_eventID = 3;
	//		_velx = 0;
	//		_attack = true;
	//		break;
	//	default: break;
	//	}
	//default: break;
	//}

	const Uint8 * keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_D]) {
		_eventID = Event::idle;
		_velx = 7;
		_flip = SDL_FLIP_NONE;
	}
	else if (keyState[SDL_SCANCODE_A]) {
		_eventID = Event::run;
		_velx = -7;
		_flip = SDL_FLIP_HORIZONTAL;
	}
	else if (keyState[SDL_SCANCODE_SPACE]) {
		_eventID = Event::attack;
		_velx = 0;
		_attack = true;
	}
	else {
		_eventID = Event::idle;
		_velx = 0;
		_attack = false;
	}

	SDL_PumpEvents();
}

void Player::pollEventsP2(SDL_Event &event)
{
	const Uint8 * keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_RIGHT]) {
		_eventID = Event::idle;
		_velx = 7;
		_flip = SDL_FLIP_NONE;
	}
	else if (keyState[SDL_SCANCODE_LEFT]) {
		_eventID = Event::run;
		_velx = -7;
		_flip = SDL_FLIP_HORIZONTAL;
	}
	else if (keyState[SDL_SCANCODE_R]) {
		_eventID = Event::attack;
		_velx = 0;
		_attack = true;
	}
	else {
		_eventID = Event::idle;
		_velx = 0;
		_attack = false;
	}
}

void Player::takeHit(Character character, int damage, Player &player)
{
	_health -= damage;

	if (_health <= 0) {
		player.~Player(); //player death
	}
}

void Player::move(Window &window)
{
	int rightWall = 0;
	int leftWall = 0;

	if (_character == Character::knight) {
		rightWall = window.getWidth() - _w;
		leftWall = 0;
	}
	else if (_character == Character::samurai) {
		rightWall = window.getWidth() - 400;
		leftWall = -200;
	}
	else if (_character == Character::huntress) {
		rightWall = window.getWidth() - 170 - 300;
		leftWall = -170;
	}

	_xPos += _velx;
	if (_xPos >= rightWall || _xPos <= leftWall)
		_xPos -= _velx;
}