#include <iostream>
#include <SDL.h>

#include "Window.h"
#include "Hero.h"
#include "Knight.h"
#include "Samurai.h"
#include "Button.h"

SDL_Event event;

Window window("DEMO", 1920, 1080);//, "Assets/backgroundMenu.png");

//void pollEvents(Window &window, Knight &knight, Samurai &samurai,
//	Button &buttonStart, Button &buttonHelp)
//{
//	SDL_Event event;
//
//	if (SDL_PollEvent(&event)) {
//		window.pollEvents(event);
//		//hero.pollEvents(event);
//		knight.pollEvents(event);
//		samurai.pollEvents(event);
//		buttonStart.pollEvents(event);
//		buttonHelp.pollEvents(event);
//	}
//}

int mainMenu(int argc, char** argv); //forward declaration

int gameLoop(int argc, char** argv)
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	//Window window("DEMO", 1920, 1080);

	//Hero hero(200, 200, 128, 128, "Assets/samurai_idle_1.png");
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

	while (window.isRunning()) {

		//if (window.getCurWindow() == Window::CurrWindow::mainMenu) {
		//	mainMenu(argc, argv, window);
		//}

		//mainMenu(argc, argv, window);

		frameStart = SDL_GetTicks();

		window.draw();
		knight.move(window);
		knight.draw(kx);
		samurai.move(window);
		samurai.draw(sx); //replace with another x;
		
		if (SDL_PollEvent(&event)) {
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

		if (kSaveEvent != knight.getEventID()) {
			kx = 60;
			kSaveEvent = knight.getEventID();
		}

		if (kAnimDel >= 5) { //delay animation //knight
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

		if (sAnimDel >= 8) { //delay animation //knight
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
	//hero.~Hero();
	knight.~Knight();
	samurai.~Samurai();

	return 0;
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
			//buttonStart.pollEvents(event);
			//buttonHelp.pollEvents(event);
			//buttonQuit.pollEvents(event);

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

	return gameLoop(argc, argv);
}

int main(int argc, char** argv)
{
	mainMenu(argc, argv);
	return 0;
}