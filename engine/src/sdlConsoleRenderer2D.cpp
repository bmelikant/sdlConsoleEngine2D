#include <sdlConsoleEngineRenderer2D.h>

const _rgb_t defaultBackColor = {0,0,0,255};

sdlConsoleEngineRenderer2D::sdlConsoleEngineRenderer2D() {
	backColor = defaultBackColor;
}

bool sdlConsoleEngineRenderer2D::init(SDL_Window *window) {
	if ((consoleRenderer = SDL_CreateRenderer(window,-1,0)) == NULL) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,"Error creating renderer: %s\n",SDL_GetError());
		return false;
	}
	return true;
}

void sdlConsoleEngineRenderer2D::destroy() {
	SDL_DestroyRenderer(consoleRenderer);
}

void sdlConsoleEngineRenderer2D::clear() {
	backColor = defaultBackColor;
	SDL_SetRenderDrawColor(consoleRenderer,backColor.r,backColor.g,backColor.b,backColor.a);
	SDL_RenderClear(consoleRenderer);
}

void sdlConsoleEngineRenderer2D::update() {
	SDL_RenderPresent(consoleRenderer);
}