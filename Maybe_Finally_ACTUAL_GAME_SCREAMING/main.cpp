#include <iostream>
#include <SDL.h>

#include "Window.h"
#include "Hero.h"
#include "Knight.h"
#include "Samurai.h"
#include "Button.h"
#include "Player.h"
#include "Hitbox.h"

SDL_Event event;

Window window("DEMO", 1920, 1080);

int mainMenu(int argc, char** argv); //forward declaration

int gameLoop(int argc, char** argv, int playerOneSel, int playerTwoSel)
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
	case 0:
		playerOneTexture = knightTexture;
		pOneXPos = 200;
		pOneYPos = window.getHeight() - 350;
		pOneInX = kx;
		pOneAnimDel = kAnimDel;
		break;
	case 1:
		playerOneTexture = samuraiTexture;
		pOneXPos = 50;
		pOneYPos = window.getHeight() - 550;
		pOneInX = sx;
		pOneAnimDel = sAnimDel;
		break;
	default: break;
	}

	switch (playerTwoSel) {
	case 0:
		playerTwoTexture = knightTexture;
		pTwoXpos = window.getWidth() - 400;
		pTwoYPos = window.getHeight() - 350;
		pTwoInX = kx;
		pTwoAnimDel = kAnimDel;
		break;
	case 1:
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

	int pOneSaveEvent = playerOne.getEventID(); //Save player 1's last event
	int pTwoSaveEvent = playerTwo.getEventID(); //Save player 2's last event

	//Hitbox hitbox(playerOneSel, 0);

	while (window.isRunning()) {
		frameStart = SDL_GetTicks();

		window.draw();

		playerOne.move(window);
		playerOne.draw(pOneInX, pOneSaveEvent, pOneAnimDel);

		playerTwo.move(window);
		playerTwo.draw(pTwoInX, pTwoSaveEvent, pTwoAnimDel);

		if (playerOne.getEventID() == 3) {
			Hitbox hitbox(playerOneSel, 0);
			hitbox.draw();
			//hitbox.~Hitbox();
		}

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

	Samurai test(200, 200, "Assets/samurai.png");

	int playerSelecting = 0;
	int playerOne = 0;
	int playerTwo = 0;

	while (window.isRunning()) {
		frameStart = SDL_GetTicks();

		window.draw();

		char1.draw();
		char2.draw();

		if (SDL_PollEvent(&event)) {
			if (char1.pollEvents(event) && playerSelecting == 0) {
				playerOne = 0;
				playerSelecting++;
			}
			else if (char1.pollEvents(event) && playerSelecting == 1) {
				playerTwo = 0;
				playerSelecting++;
			}

			if (char2.pollEvents(event) && playerSelecting == 0) {
				playerOne = 1;
				playerSelecting++;
			}
			else if (char2.pollEvents(event) && playerSelecting == 1) {
				playerTwo = 1;
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
			else if (buttonQuit.pollEvents(event))
				window.terminate();
		}

		if (window.getCurWindow() == Window::CurrWindow::game)
			break;
	}

	buttonStart.~Button();
	buttonHelp.~Button();
	buttonQuit.~Button();

	return characterSelection(argc, argv);
}

int main(int argc, char** argv)
{
	mainMenu(argc, argv);
	return 0;
}