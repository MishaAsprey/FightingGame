#include <iostream>
#include <SDL.h>

#include "Window.h"
#include "Hero.h"
#include "Knight.h"
#include "Samurai.h"
#include "Button.h"
#include "Player.h"

SDL_Event event;

Window window("DEMO", 1920, 1080);

int mainMenu(int argc, char** argv); //forward declaration

int gameLoop(int argc, char** argv, int playerOneSel, int playerTwoSel)
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Knight knight(200, window.getHeight() - 350, "Assets/knight.png");
	Samurai samurai(window.getWidth() - 600, window.getHeight() - 550, "Assets/samurai.png");

	window.setWindowTexture("Assets/backgroundGameScene1.png");

	int kSaveEvent = knight.getEventID();
	int sSaveEvent = samurai.getEventID();

	int sInitial = 0; //120;

	int kx = 60; //90-21; //initial x for knight sprite
	int sx = sInitial; //initial x for samurai sprite
	int kAnimDel = 0; //animation delay: knight
	int sAnimDel = 0; //animation delay: samurai

	const char * knightTexture = "Assets/knight.png";
	const char * samuraiTexture = "Assets/samurai.png";

	const char * playerOneTexture = "";
	int pOneInX = 0;
	int pOneAnimDel = 0;

	const char * playerTwoTexture = "";
	int pTwoInX = 0;
	int pTwoAnimDel = 0;

	switch (playerOneSel) {
	case 0:
		playerOneTexture = knightTexture;
		pOneInX = kx;
		pOneAnimDel = kAnimDel;
		break;
	case 1:
		playerOneTexture = samuraiTexture;
		pOneInX = kx;
		pOneAnimDel = sAnimDel;
		break;
	default: break;
	}

	switch (playerTwoSel) {
	case 0:
		playerTwoTexture = knightTexture;
		pTwoInX = kx;
		pTwoAnimDel = kAnimDel;
		break;
	case 1:
		playerTwoTexture = samuraiTexture;
		pTwoInX = sx;
		pTwoAnimDel = sAnimDel;
		break;
	default: break;
	}

	Player playerOne(200, 200, playerOneTexture);
	Player playerTwo(600, 100, playerTwoTexture);

	int pOneSaveEvent = playerOne.getEventID(); //Save player 1's last event
	int pTwoSaveEvent = playerTwo.getEventID(); //Save player 2's last event

	while (window.isRunning()) {

		//if (window.getCurWindow() == Window::CurrWindow::mainMenu) {
		//	mainMenu(argc, argv, window);
		//}

		frameStart = SDL_GetTicks();

		window.draw();
		knight.move(window);
		knight.draw(kx);
		samurai.move(window);
		samurai.draw(sx);

		//playerOne.move(window, 0);
		//playerOne.drawKnight(kx, pOneSaveEvent, kAnimDel);

		//playerTwo.move(window, 1);
		//playerTwo.drawSamurai(sx, pTwoSaveEvent, sAnimDel);

		playerOne.move(window, playerOneSel);
		playerOne.draw(pOneInX, playerOneSel, pOneSaveEvent, pOneAnimDel);

		playerTwo.move(window, playerTwoSel);
		playerTwo.draw(pTwoInX, playerTwoSel, pTwoSaveEvent, pTwoAnimDel);


		//if (playerOneSel == 0) {
		//	playerOne.move(window, 0);
		//	playerOne.drawKnight(kx, pOneSaveEvent, kAnimDel);
		//}
		//else {
		//	playerOne.move(window, 1);
		//	playerOne.drawSamurai(sx, pOneSaveEvent, sAnimDel);
		//}

		//if (playerTwoSel == 0) {
		//	playerTwo.move(window, 0);
		//	playerTwo.drawKnight(kx, pOneSaveEvent, kAnimDel);
		//}
		//else {
		//	playerTwo.move(window, 1);
		//	playerTwo.drawSamurai(sx, pOneSaveEvent, sAnimDel);
		//}

		//switch (playerOneSel) {
		//case 0:
		//	playerOne.move(window, 0);
		//	playerOne.drawKnight(kx, pOneSaveEvent, kAnimDel);
		//	break;
		//case 1:
		//	playerOne.move(window, 1);
		//	playerOne.drawSamurai(sx, pOneSaveEvent, sAnimDel);
		//	break;
		//default: break;
		//}

		//switch (playerTwoSel) {
		//case 0:
		//	playerTwo.move(window, 0);
		//	playerTwo.drawKnight(kx, pOneSaveEvent, kAnimDel);
		//	break;
		//case 1:
		//	playerTwo.move(window, 1);
		//	playerTwo.drawSamurai(sx, pOneSaveEvent, sAnimDel);
		//	break;
		//default: break;
		//}

		//playerOne.draw(sx);
		//playerOne.move(window);

		if (SDL_PollEvent(&event)) {
			playerOne.pollEventsP1(event);
			playerTwo.pollEventsP2(event);

			knight.pollEvents(event);
			samurai.pollEvents(event);
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

		///////////////////////////////////////////

		//if (pOneSaveEvent != playerOne.getEventID()) {
		//	kx = 60;
		//	pOneSaveEvent = playerOne.getEventID();
		//}

		//if (kAnimDel >= 5) { //animation delay for knight
		//	kx += 180;

		//	int limit = 1800;
		//	if (playerOne.isRunning())
		//		limit = 1440;
		//	else if (playerOne.attack())
		//		limit = 1260;

		//	if (kx >= limit) {
		//		kx = 60; //90-21
		//	}
		//	kAnimDel = 0;
		//}

		///////////////////////////////////////////


		if (kSaveEvent != knight.getEventID()) {
			kx = 60;
			kSaveEvent = knight.getEventID();
		}

		if (kAnimDel >= 5) { //animation delay for knight
			kx += 180;

			int limit = 1800;
			if (knight.isRunning())
				limit = 1440;
			else if (knight.attack())
				limit = 1260;

			if (kx >= limit) {
				kx = 60; //90-21
			}
			kAnimDel = 0;
		}

		if (sSaveEvent != samurai.getEventID()) {
			sx = sInitial;
			sSaveEvent = samurai.getEventID();
		}

		if (sAnimDel >= 8) { //animation delay for knight
			sx += 200;

			int limit = 800;
			if (samurai.isRunning())
				limit = 1600;
			else if (samurai.attack())
				limit = 800;

			if (sx >= limit)
				sx = sInitial; //90-21
			sAnimDel = 0;
		}
	}

	window.~Window();
	knight.~Knight();
	samurai.~Samurai();
	playerOne.~Player();
	playerTwo.~Player();

	return 0;
}

//template <typename T>
//T definePlayerOne(T character) {
//	return character;
//}

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

		//SDL_Rect one { 500, 500, 200, 200 };
		//SDL_Rect two { 800, 500, 200, 200 };
		//SDL_RenderDrawRect(window.renderer, &one);
		//SDL_RenderDrawRect(window.renderer, &two);
		//SDL_RenderFillRect(window.renderer, &one);
		//SDL_RenderFillRect(window.renderer, &two);

		//playerOne = new Samurai(200, 200, "da");

		//auto playerOne = definePlayerOne(new Knight(20, 20, "da"));

		//auto playerOne = std::nullptr_t;

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

	//return gameLoop(argc, argv);
	return characterSelection(argc, argv);
}

int main(int argc, char** argv)
{
	mainMenu(argc, argv);
	return 0;
}