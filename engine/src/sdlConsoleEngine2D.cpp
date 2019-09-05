#include <sdlConsoleEngine.h>

#include <iostream>

using namespace std;

static const _rgb_t colorPalette[8] = {
	{0,0,0,255},
	{255,0,0,255},
	{0,255,0,255},
	{0,0,255,255},
	{127,127,127,255},
	{127,0,0,255},
	{0,127,0,255},
	{0,0,127,255}
};
static int nPaletteIndex = 0;

/**  static helper calculation methods */
static double getElapsedTimeMs(Uint64 nCurrentTimestamp, Uint64 nLastTimestamp) {
	return (double)((nCurrentTimestamp - nLastTimestamp)*1000) / SDL_GetPerformanceFrequency();
}

/**
 * basic constructor method
 */
sdlConsoleEngine2D::sdlConsoleEngine2D() {
	running = true;
	refresh = true;
	nFrameCount = 0;
	fCurrentFps = 0.0f;
	fLastFrameSample = 0.0f;
}

/**
 * Constructor method to make a console of a given size. Creates a windowed console
 */
sdlConsoleEngine2D::sdlConsoleEngine2D(int nWidth, int nHeight) : sdlConsoleEngine2D() {
	if (nWidth > 0 && nHeight > 0) {
		nConsoleWidth = nWidth;
		nConsoleHeight = nHeight;
		nConsoleWindowFlags = SDL_WINDOW_RESIZABLE;
	}
}

/**
 * Calling this function will start the main game loop.
 */
int sdlConsoleEngine2D::onExecute() {
	if (onInit() == false) {
		return -1;
	}

	SDL_Event event;
	Uint64 lTimestampStart = SDL_GetPerformanceCounter();

	while (running) {
		// compute the time taken by the last frame
		Uint64 lTimestampDelta = SDL_GetPerformanceCounter();
		double fElapsedTime =  getElapsedTimeMs(lTimestampDelta,lTimestampStart);
		lTimestampStart = lTimestampDelta;

		// compute the current FPS
		doFrameRate(fElapsedTime);
		// check for events
		while (SDL_PollEvent(&event)) {
			onEvent(&event);
		}

		// should we calculate the elapsed time again for accuracy following the framerate calculation? it isn't very expensive...
		onLoop(fElapsedTime);
		onRender();

		// if we want to lock the frame rate, do it here
		lockFrameRate(lTimestampStart);
	}

	onCleanup();
	return 0;
}

bool sdlConsoleEngine2D::onInit() {
	// try to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	// and TTF
	if (TTF_Init() < 0) {
		return false;
	}

	// make sure we can display this resolution; otherwise, default to normal fullscreen console mode
	SDL_DisplayMode desktopMode;
	if (SDL_GetDesktopDisplayMode(0, &desktopMode) != 0) {
		SDL_Log("SDL_GetDesktopDisplayMode() returned %s\n", SDL_GetError());
	}

	if (nConsoleWidth > desktopMode.w || nConsoleHeight > desktopMode.h) {
		SDL_Log("Unsupported resolution requested. Setting to default values");
		setConsoleModeToDefault();
	}

	// and the main window (fullscreen at this point, can be overridden)
	if (consoleWindow = SDL_CreateWindow("Console Engine 2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		nConsoleWidth,nConsoleHeight,nConsoleWindowFlags)) {
		if (!renderer.init(consoleWindow)) {
			return false;
		}
	} else {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,"Error creating console window: %s\n", SDL_GetError());
		return false;
	}

	// now let's clear and update the console renderer
	renderer.clear();
	renderer.update();

	return true;
}

/**
 * This function is called whenever an event takes place. This function can be overridden
 * without calling the base method as long as the engine implementation takes care of
 * things like exiting the game
 */
void sdlConsoleEngine2D::onEvent(SDL_Event *event) {
	if (event->type == SDL_QUIT) {
		running = false;
	} else if (event->type == SDL_KEYUP) {
		if (event->key.keysym.scancode == SDL_SCANCODE_A) {
			if (nPaletteIndex < 7) nPaletteIndex++;
			else nPaletteIndex = 0;
			refresh = true;
		} else if (event->key.keysym.scancode == SDL_SCANCODE_D) {
			if (nPaletteIndex > 0) nPaletteIndex--;
			else nPaletteIndex = 7;
			refresh = true;
		}
	}
}

/**
 * This function is called on each loop. This is where derived classes
 * should perform their work such as updating AI
 */
void sdlConsoleEngine2D::onLoop(double fDeltaTime) {
	renderer.fillBackground(colorPalette[nPaletteIndex]);
}

/**
 * This function is called on each loop to render
 */
void sdlConsoleEngine2D::onRender() {
	// redraw the window when a key is pressed
	renderer.update();
}

/**
 * Called at the end of the onExecute main loop to destroy the game
 * Derived classes can call this to destroy the game context. If overridden,
 * this function must either call the base function or call SDL_Quit()
 */
void sdlConsoleEngine2D::onCleanup() {
	// pretty simple basic function: just quit SDL
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"onCleanup() called, deleting render context and window");
	renderer.destroy();
	SDL_DestroyWindow(consoleWindow);
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"calling SDL_Quit()");
	SDL_Quit();
}

double sdlConsoleEngine2D::getFPS() {
	return fCurrentFps;
}

void sdlConsoleEngine2D::setMaxFPS(int fMaxFPS) {
	if (fMaxFPS == 0) {
		// unlock the framerate
		bFrameRateLocked = false;
		fMillisPerFrame = 0.0f;
	} else {
		bFrameRateLocked = true;
		fMillisPerFrame = 1.0f / ((double)fMaxFPS*0.001f);
	}
}

/** private member functions */

void sdlConsoleEngine2D::setConsoleModeToDefault() {
	nConsoleWidth = 640;
	nConsoleHeight = 480;
	nConsoleWindowFlags = SDL_WINDOW_RESIZABLE;
}

void sdlConsoleEngine2D::doFrameRate(double fElapsedTime) {
	nFrameCount++;
	fLastFrameSample += fElapsedTime;
	if (fLastFrameSample > 50) {
		fCurrentFps = (double)(nFrameCount) / (fLastFrameSample*0.001f);
		nFrameCount = 0;
		fLastFrameSample = 0.0f;
	}
}

void sdlConsoleEngine2D::lockFrameRate(Uint64 nLastTimeStamp) {
	if (bFrameRateLocked) {
		Uint64 nLast = nLastTimeStamp;
		Uint64 nCurrent = SDL_GetPerformanceCounter();
		double fCurrentFrameTime = getElapsedTimeMs(nCurrent,nLast);

		if (fCurrentFrameTime < fMillisPerFrame) {
			nLast = nCurrent;
			while (fCurrentFrameTime < fMillisPerFrame) {
				nCurrent = SDL_GetPerformanceCounter();
				fCurrentFrameTime += getElapsedTimeMs(nCurrent,nLast);
				nLast = nCurrent;
			}
		}
	}
}