#ifndef _SDL_CONSOLE_ENGINE_CANVAS_2D
#define _SDL_CONSOLE_ENGINE_CANVAS_2D

#include <SDL.h>
#include <SDL_ttf.h>

struct COLOR_RGB {
	int r,g,b,a;
};

using _rgb_t = struct COLOR_RGB;

class sdlConsoleEngineRenderer2D {
private:
	SDL_Renderer *consoleRenderer;
	TTF_Font *font;

	_rgb_t backColor;
	_rgb_t foreColor;

public:
	sdlConsoleEngineRenderer2D();
	bool init(SDL_Window *);
	void destroy();

// drawing methods
public:
	void update();
	void clear();

	_rgb_t fillBackground(_rgb_t newBackColor);

	void drawText(const char *text, int x, int y);
};

#endif