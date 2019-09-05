#ifndef _SDL_CONSOLE_ENGINE_CANVAS_2D
#define _SDL_CONSOLE_ENGINE_CANVAS_2D

#include <SDL.h>

struct COLOR_RGB {
	int r,g,b,a;
};

using _rgb_t = struct COLOR_RGB;

class sdlConsoleEngineRenderer2D {
private:
	SDL_Renderer *consoleRenderer;
	_rgb_t backColor;

public:
	sdlConsoleEngineRenderer2D();
	bool init(SDL_Window *);
	void destroy();

// drawing methods
public:
	void update();
	void clear();
	_rgb_t fillBackground(_rgb_t newBackColor);

};

#endif