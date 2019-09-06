#ifndef _SDL_ENGINE_H
#define _SDL_ENGINE_H

#include "sdlConsoleEngineRenderer2D.h"

#include <SDL.h>
#include <SDL_ttf.h>

class sdlConsoleEngine2D {
private:
	bool running;
	bool refresh;
	bool bFrameRateLocked;
	SDL_Window *consoleWindow;

	/** frame rate tracking variables */
	unsigned long nFrameCount;
	double fLastFrameSample;
	double fCurrentFps;
	double fMillisPerFrame;

	int nConsoleWidth = 640;
	int nConsoleHeight = 480;
	int nConsoleWindowFlags = SDL_WINDOW_RESIZABLE;

protected:

	sdlConsoleEngineRenderer2D renderer;

public:
	sdlConsoleEngine2D();
	sdlConsoleEngine2D(int nWidth, int nHeight);
	int onExecute();

public:
	/** these functions should be overridden in derived engines (duh!!!) */
	virtual bool onUserInit() = 0;
	virtual void onUserEvent(SDL_Event *) = 0;
	virtual void onUserLoop(double fDeltaTime) = 0;
	
	double getFPS();
	void setMaxFPS(int fMaxFPS);

private:

	bool onInit();
	void onEvent(SDL_Event *);
	void onLoop(double fDeltaTime);
	void onCleanup();

	void doClearRender();
	void onRender();
	void setConsoleModeToDefault();
	void doFrameRate(double fTimeElapsed);
	void lockFrameRate(Uint64 nLastTimeStamp);
};

#endif