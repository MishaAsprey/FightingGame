#include <iostream>
#include <SDL.h>

#include "Window.h"
#include "Hero.h"
#include "Knight.h"
#include "Samurai.h"
#include "Button.h"
#include "Player.h"
#include "Hitbox.h"
#include "Hurtbox.h"

SDL_Event event;

Window window("DEMO", 1920, 1080);

int mainMenu(int argc, char** argv); //forward declaration
int helpScreen(int argc, char** argv); //forward declaration

int gameLoop(int argc, char** argv, Character playerOneSel, Character playerTwoSel)
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	window.setWindowTexture("Assets/backgroundGameScene1.png");

	int sInitial = 0; //120;

	int kx = 60; //90-21; //initial x for knight sprite
	int sx = sInitial; //initial x for samurai sprite
	int kAnimDel = 0; //animation delay: knight
	int sAnimDel = 0; //animation delay: samurai

	const char * knightTexture = "Assets/knight.png";
	const char * samuraiTexture = "Assets/samurai.png";

	const char * playerOneTexture = "";
	int pOneXPos = 0;
	int pOneYPos = 0;
	int pOneInX = 0;
	int pOneAnimDel = 0;

	const char * playerTwoTexture = "";
	int pTwoXpos = 0;
	int pTwoYPos = 0;
	int pTwoInX = 0;
	int pTwoAnimDel = 0;

	switch (playerOneSel) {
	case Character::knight:
		playerOneTexture = knightTexture;
		pOneXPos = 200;
		pOneYPos = window.getHeight() - 350;
		pOneInX = kx;
		pOneAnimDel = kAnimDel;
		break;
	case Character::samurai:
		playerOneTexture = samuraiTexture;
		pOneXPos = 50;
		pOneYPos = window.getHeight() - 550;
		pOneInX = sx;
		pOneAnimDel = sAnimDel;
		break;
	default: break;
	}

	switch (playerTwoSel) {
	case Character::knight:
		playerTwoTexture = knightTexture;
		pTwoXpos = window.getWidth() - 400;
		pTwoYPos = window.getHeight() - 350;
		pTwoInX = kx;
		pTwoAnimDel = kAnimDel;
		break;
	case Character::samurai:
		playerTwoTexture = samuraiTexture;
		pTwoXpos = window.getWidth() - 600;
		pTwoYPos = window.getHeight() - 550;
		pTwoInX = sx;
		pTwoAnimDel = sAnimDel;
		break;
	default: break;
	}

	Player playerOne(pOneXPos, pOneYPos, playerOneTexture, SDL_FLIP_NONE, playerOneSel, 0);
	Player playerTwo(pTwoXpos, pTwoYPos, playerTwoTexture, SDL_FLIP_HORIZONTAL, playerTwoSel, 1);

	Hurtbox hurtBoxPlayerOne(playerOneSel, 0, playerOne.getXpos(), playerOne.getYpos(), playerOne.getFlip());
	Hurtbox hurtBoxPlayerTwo(playerTwoSel, 1, playerTwo.getXpos(), playerTwo.getYpos(), playerTwo.getFlip());

	int pOneSaveEvent = playerOne.getEventID(); //Save player 1's last event
	int pTwoSaveEvent = playerTwo.getEventID(); //Save player 2's last event

	//Hitbox hitbox(playerOneSel, 0);

	while (window.isRunning()) {
		frameStart = SDL_GetTicks();

		window.draw();

		if (playerOne.getEventID() == 3) {
			Hitbox hitbox(playerOneSel, 0, playerOne.getXpos(), playerOne.getYpos(), playerOne.getFlip());
			hitbox.draw();
		}
		if (playerTwo.getEventID() == 3) {
			Hitbox hitbox(playerTwoSel, 1, playerTwo.getXpos(), playerTwo.getYpos(), playerTwo.getFlip());
			hitbox.draw();
		}

		hurtBoxPlayerOne.draw(playerOneSel, playerOne.getXpos());
		hurtBoxPlayerTwo.draw(playerTwoSel, playerTwo.getXpos());

		playerOne.move(window);
		playerOne.draw(pOneInX, pOneSaveEvent, pOneAnimDel);

		playerTwo.move(window);
		playerTwo.draw(pTwoInX, pTwoSaveEvent, pTwoAnimDel);

		//if (playerOne.getEventID() == 3) {
		//	Hitbox hitbox(playerOneSel, 0, playerOne.getXpos(), playerOne.getYpos(), playerOne.getFlip());
		//	hitbox.draw();
		//	//hitbox.~Hitbox();
		//}
		//if (playerTwo.getEventID() == 3) {
		//	Hitbox hitbox(playerTwoSel, 1, playerTwo.getXpos(), playerTwo.getYpos(), playerTwo.getFlip());
		//	hitbox.draw();
		//}

		if (SDL_PollEvent(&event)) {
			playerOne.pollEventsP1(event);
			playerTwo.pollEventsP2(event);
			window.pollEvents(event);
		}

		window.clear();
		kAnimDel++;
		sAnimDel++;

		frameTime = SDL_GetTicks() - frameStart;

		if (window.getCurWindow() == Window::CurrWindow::mainMenu)
			return mainMenu(argc, argv);

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	window.~Window();
	playerOne.~Player();
	playerTwo.~Player();

	return 0;
}

int characterSelection(int argc, char** argv)
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	int buttonCentrePos = window.getWidth() / 2 - 128;

	Button char1(buttonCentrePos, 200, "Assets/ButtonStart.png");
	Button char2(buttonCentrePos, 400, "Assets/ButtonHelp.png");

	//Knight knight(window.getWidth() / 2, window.getHeight() / 2, "Assets/knight.png");
	//Samurai samurai(window.getWidth() / 2, window.getHeight() / 2, "Assets/samurai.png");

	Player knight(window.getWidth() / 2, window.getHeight() / 2,
		"Assets/knight.png", SDL_FLIP_NONE, Character::knight, 0);
	Player samurai(window.getWidth() / 2, window.getHeight() / 2,
		"Assets/samurai.png", SDL_FLIP_NONE, Character::samurai, 0);

	int playerSelecting = 0;
	Character playerOne = Character::knight;
	Character playerTwo = Character::knight;

	while (window.isRunning()) {
		frameStart = SDL_GetTicks();

		window.draw();

		char1.draw();
		char2.draw();

		if (SDL_PollEvent(&event)) {
			if (char1.pollEvents(event) && playerSelecting == 0) {
				playerOne = Character::knight;
				playerSelecting++;
			}
			else if (char1.pollEvents(event) && playerSelecting == 1) {
				playerTwo = Character::knight;
				playerSelecting++;
			}

			if (char2.pollEvents(event) && playerSelecting == 0) {
				playerOne = Character::samurai;
				playerSelecting++;
			}
			else if (char2.pollEvents(event) && playerSelecting == 1) {
				playerTwo = Character::samurai;
				playerSelecting++;
			}
		}
		window.clear();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
		if (playerSelecting >= 2)
			break;

	}
	char1.~Button();
	char2.~Button();

	return gameLoop(argc, argv, playerOne, playerTwo);
}

int mainMenu(int argc, char** argv)
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	int buttonCentrePos = window.getWidth() / 2 - 128;

	Button buttonStart(buttonCentrePos, 200, "Assets/ButtonStart.png");
	Button buttonHelp(buttonCentrePos, 400, "Assets/ButtonHelp.png");
	Button buttonQuit(buttonCentrePos, 600, "Assets/ButtonQuit.png");

	window.setWindowTexture("Assets/backgroundMenu.png");

	while (window.isRunning()) {
		frameStart = SDL_GetTicks();

		window.draw();
		buttonStart.draw();
		buttonHelp.draw();
		buttonQuit.draw();

		window.clear();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);

		if (SDL_PollEvent(&event)) {
			if (buttonStart.pollEvents(event))
				window.setCurWindow(Window::CurrWindow::game);
			else if (buttonHelp.pollEvents(event))
				window.setCurWindow(Window::CurrWindow::help);
			else if (buttonQuit.pollEvents(event))
				window.terminate();
		}

		if (window.getCurWindow() != Window::CurrWindow::mainMenu)
			break;
	}

	buttonStart.~Button();
	buttonHelp.~Button();
	buttonQuit.~Button();

	if (window.getCurWindow() == Window::CurrWindow::game)
		return characterSelection(argc, argv);
	else if (window.getCurWindow() == Window::CurrWindow::help)
		return helpScreen(argc, argv);
	return 0;
}

int helpScreen(int argc, char** argv)
{
	int buttonCentrePos = window.getWidth() / 2 - 128;

	Button buttonBack(buttonCentrePos, 600, "Assets/ButtonHelp.png");

	while (window.isRunning()) {
		window.draw();
		buttonBack.draw();
		window.clear();

		if (SDL_PollEvent(&event)) {
			window.pollEvents(event);
			if (buttonBack.pollEvents(event))
				window.setCurWindow(Window::CurrWindow::mainMenu);
		}

		if (window.getCurWindow() == Window::CurrWindow::mainMenu)
			break;
	}

	buttonBack.~Button();

	return mainMenu(argc, argv);
}

int main(int argc, char** argv)
{
	mainMenu(argc, argv);
	return 0;
}