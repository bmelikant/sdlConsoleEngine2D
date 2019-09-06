#ifndef _SDL_CONSOLE_ENGINE_CANVAS_2D
#define _SDL_CONSOLE_ENGINE_CANVAS_2D

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

struct POINT {
	float x;
	float y;
};

using Point = struct POINT;
using Color = SDL_Color;

const Color COLOR_RED = {255,0,0,255};
const Color COLOR_GREEN = {0,255,0,255};
const Color COLOR_BLUE = {0,0,255,255};
const Color COLOR_GREY = {128,128,128,0};

class sdlConsoleEngineRenderer2D {
private:
	SDL_Renderer *consoleRenderer;
	TTF_Font *font;

	Color backColor;
	Color foreColor;

public:
	sdlConsoleEngineRenderer2D();
	bool init(SDL_Window *);
	void destroy();

// drawing methods
public:
	void update();
	void clear();

	Color setBackColor(Color newColor);
	Color setForeColor(Color newColor);
	Color fillBackground(Color newBackColor);
	void setFont(std::string fontFileName, int pointSize);

	void drawText(const char *text, int x, int y);

	void drawLine(Point src, Point dst);
	void drawLine(Point src, Point dest, Color color);

	void drawTriangle(Point a, Point b, Point c);
	void drawTriangle(Point a, Point b, Point c, Color color);
	void fillTriangle(Point a, Point b, Point c, Color color);

private:

	void fillFlatBottomTriangle(Point a, Point b, Point c, Color color);
	void fillFlatTopTriangle(Point a, Point b, Point c, Color color);
};

#endif