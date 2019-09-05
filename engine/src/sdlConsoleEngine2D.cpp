#include <sdlConsoleEngine.h>

#include <iostream>

using namespace std;

/**
 * basic constructor method
 */
sdlConsoleEngine2D::sdlConsoleEngine2D() {
	running = true;
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
	while (running) {
		while (SDL_PollEvent(&event)) {
			onEvent(&event);
		}
		onLoop(0.0f);
		onRender();
	}

	onCleanup();
	return 0;
}

bool sdlConsoleEngine2D::onInit() {
	// try to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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
	}
}

/**
 * This function is called on each loop. This is where derived classes
 * should perform their work
 */
void sdlConsoleEngine2D::onLoop(float fDeltaTime) {
}

/**
 * This function is called on each loop to render
 */
void sdlConsoleEngine2D::onRender() {
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

/** private member functions */

void sdlConsoleEngine2D::setConsoleModeToDefault() {
	nConsoleWidth = 640;
	nConsoleHeight = 480;
	nConsoleWindowFlags = SDL_WINDOW_RESIZABLE;
}