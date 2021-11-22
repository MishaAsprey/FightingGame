#include <iostream>
#include <SDL.h>

#include <vector>

#include "Window.h"
#include "Hero.h"
#include "Knight.h"
#include "Samurai.h"
#include "Button.h"
#include "Player.h"

SDL_Event event;

Window window("DEMO", 1920, 1080);

int mainMenu(int argc, char** argv); //forward declaration

int gameLoop(int argc, char** argv)
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Knight knight(200, window.getHeight() - 350, "Assets/knight.png");
	Samurai samurai(window.getWidth() - 600, window.getHeight() - 550, "Assets/samurai.png");

	Player playerOne(200, 200, "Assets/knight.png");

	window.setWindowTexture("Assets/backgroundGameScene1.png");

	int kSaveEvent = knight.getEventID();
	int sSaveEvent = samurai.getEventID();

	int pOneSaveEvent = playerOne.getEventID();

	int sInitial = 0; //120;

	int kx = 60; //90-21; //initial x for knight sprite
	int sx = sInitial; //initial x for samurai sprite
	int kAnimDel = 0; //animation delay: knight
	int sAnimDel = 0; //animation delay: samurai

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

		playerOne.move(window);
		playerOne.drawKnight(kx, pOneSaveEvent, kAnimDel);

		//playerOne.draw(sx);
		//playerOne.move(window);

		if (SDL_PollEvent(&event)) {
			playerOne.pollEventsP1(event);

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

	return 0;
}

template <typename T>
T definePlayerOne(T character) {
	return character;
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
			if (char1.pollEvents(event)) {
				definePlayerOne(Knight(200, 200, "Assets/knight.png"));
			}
		}

		//auto playerOne = 

		window.clear();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);

		SDL_Delay(1000);
		char1.~Button();
		char2.~Button();
		return gameLoop(argc, argv);
	}

	return gameLoop(argc, argv);
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