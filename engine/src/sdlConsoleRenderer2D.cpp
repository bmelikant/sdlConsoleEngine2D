#include <sdlConsoleEngineRenderer2D.h>
#include <SDL_ttf.h>

#include <vector>
#include <algorithm>
#include <sstream>

const Color defaultBackColor = {0,0,0,255};
const Color defaultForeColor = {180,180,180,255};

sdlConsoleEngineRenderer2D::sdlConsoleEngineRenderer2D() {
	backColor = defaultBackColor;
	foreColor = defaultForeColor;
}

bool sdlConsoleEngineRenderer2D::init(SDL_Window *window) {
	if ((consoleRenderer = SDL_CreateRenderer(window,-1,0)) == NULL) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,"Error creating renderer: %s\n",SDL_GetError());
		return false;
	}
	if (TTF_Init() < 0) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,"TTF library could not be initialized");
		return false;
	}

	font = nullptr;
	return true;
}

void sdlConsoleEngineRenderer2D::destroy() {
	if (font != nullptr) {
		TTF_CloseFont(font);
	}
	TTF_Quit();
	SDL_DestroyRenderer(consoleRenderer);
}

void sdlConsoleEngineRenderer2D::clear() {
	backColor = defaultBackColor;
	SDL_SetRenderDrawColor(consoleRenderer,backColor.r,backColor.g,backColor.b,backColor.a);
	SDL_RenderClear(consoleRenderer);
}

Color sdlConsoleEngineRenderer2D::setBackColor(Color newColor) {
	Color currentBackColor = backColor;
	backColor = newColor;
	return currentBackColor;
}

Color sdlConsoleEngineRenderer2D::setForeColor(Color newColor) {
	Color oldForeColor = foreColor;
	foreColor = newColor;
	return oldForeColor;
}

Color sdlConsoleEngineRenderer2D::fillBackground(Color newColor) {
	Color currentColor = backColor;
	backColor = newColor;
	SDL_SetRenderDrawColor(consoleRenderer,backColor.r,backColor.g,backColor.b,backColor.a);
	SDL_RenderClear(consoleRenderer);
}

void sdlConsoleEngineRenderer2D::setFont(std::string fontFileName, int pointSize) {
	TTF_Font *newFont = TTF_OpenFont(fontFileName.c_str(), pointSize);
	if (newFont != nullptr) {
		// free the old font and set the new one
		TTF_CloseFont(font);
		font = newFont;
	} else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Could not open requested font: %s\n",fontFileName.c_str());
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"The error was: %s\n", TTF_GetError());
	}
}

void sdlConsoleEngineRenderer2D::drawText(const char *text, int x, int y) {
	// make sure we have a font open
	if (font != nullptr) {
		SDL_Color textColor = foreColor;
		SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(consoleRenderer,textSurface);

		SDL_Rect textRect;
		textRect.x = x;
		textRect.y = y;
		textRect.w = textSurface->w;
		textRect.h = textSurface->h;

		SDL_FreeSurface(textSurface);
		SDL_RenderCopy(consoleRenderer, texture, NULL, &textRect);
		SDL_DestroyTexture(texture);
	}
}

void sdlConsoleEngineRenderer2D::drawLine(Point src, Point dst) {
	drawLine(src,dst,foreColor);
}

void sdlConsoleEngineRenderer2D::drawTriangle(Point a, Point b, Point c) {
	drawTriangle(a,b,c,foreColor);
}

void sdlConsoleEngineRenderer2D::drawLine(Point src, Point dst, Color c) {
	SDL_SetRenderDrawColor(consoleRenderer,c.r,c.g,c.b,c.a);
	SDL_RenderDrawLine(consoleRenderer, src.x, src.y, dst.x, dst.y);
}

void sdlConsoleEngineRenderer2D::drawTriangle(Point a, Point b, Point c, Color color) {
	// draw a line between the points!!!
	drawLine(a,b,color);
	drawLine(b,c,color);
	drawLine(a,c,color);
}

void sortPoints(Point &one, Point &two, Point &three) {
	if (one.y > two.y) {
		Point temp = one;
		one = two;
		two = temp;
		sortPoints(one, two, three);
	} else if (two.y > three.y) {
		Point temp = two;
		two = three;
		three = temp;
		sortPoints(one,two,three);
	}
}

void sdlConsoleEngineRenderer2D::fillTriangle(Point a, Point b, Point c, Color color) {
	Point v1 = a, v2 = b, v3 = c;
	sortPoints(v1,v2,v3);

	if (v2.y == v3.y) {
		fillFlatBottomTriangle(v1,v2,v3,color);
	} else if (v1.y == v2.y) {
		fillFlatTopTriangle(v1,v2,v3,color);
	} else {
		Point v4 = {
			(v1.x + (((v2.y - v1.y) / (v3.y - v1.y)) * (v3.x - v1.x))),
			v2.y
		};

		fillFlatBottomTriangle(v1,v2,v4,color);
		fillFlatTopTriangle(v2,v4,v3,color);
	}
}

void sdlConsoleEngineRenderer2D::update() {
	SDL_RenderPresent(consoleRenderer);
}

/** sdlConsoleEngineRenderer2D private functions */

void sdlConsoleEngineRenderer2D::fillFlatBottomTriangle(Point a, Point b, Point c, Color color) {
	// calculate the change in x for each step
	float invslope1 = (b.x - a.x) / (b.y - a.y);
	float invslope2 = (c.x - a.x) / (c.y - a.y);

	float xPointOne = a.x;
	float xPointTwo = a.x;

	for (float lineY = a.y; lineY <= b.y; lineY++) {
		drawLine({xPointOne,lineY},{xPointTwo,lineY},color);
		xPointOne += invslope1;
		xPointTwo += invslope2;
	}
}

void sdlConsoleEngineRenderer2D::fillFlatTopTriangle(Point a, Point b, Point c, Color color) {
	float invslope1 = (c.x - a.x) / (c.y - a.y);
	float invslope2 = (c.x - b.x) / (c.y - b.y);

	float xPointOne = c.x;
	float xPointTwo = c.x;

	for (float lineY = c.y; lineY > a.y; lineY--) {
		drawLine({xPointOne,lineY},{xPointTwo,lineY},color);
		xPointOne -= invslope1;
		xPointTwo -= invslope2;
	}
}