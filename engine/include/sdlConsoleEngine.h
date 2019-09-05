#ifndef _SDL_ENGINE_H
#define _SDL_ENGINE_H

#include "sdlConsoleEngineRenderer2D.h"

#include <SDL.h>

class sdlConsoleEngine2D {
private:
	bool running;
	SDL_Window *consoleWindow;
	sdlConsoleEngineRenderer2D renderer;

	int nConsoleWidth = 640;
	int nConsoleHeight = 480;
	int nConsoleWindowFlags = SDL_WINDOW_RESIZABLE;

public:
	sdlConsoleEngine2D();
	sdlConsoleEngine2D(int nWidth, int nHeight);
	int onExecute();

public:
	bool onInit();
	void onEvent(SDL_Event *);
	void onLoop(float fDeltaTime);
	void onRender();
	void onCleanup();

private:

	void setConsoleModeToDefault();
};

#endif