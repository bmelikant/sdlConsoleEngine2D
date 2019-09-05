#include <sdlConsoleEngineRenderer2D.h>
#include <SDL_ttf.h>

const _rgb_t defaultBackColor = {0,0,0,255};
const _rgb_t defaultForeColor = {180,180,180,255};

sdlConsoleEngineRenderer2D::sdlConsoleEngineRenderer2D() {
	backColor = defaultBackColor;
	foreColor = defaultForeColor;
}

bool sdlConsoleEngineRenderer2D::init(SDL_Window *window) {
	if ((consoleRenderer = SDL_CreateRenderer(window,-1,0)) == NULL) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,"Error creating renderer: %s\n",SDL_GetError());
		return false;
	}
	font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",20);
	if (font == NULL) {
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,"Could lot load font");
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

_rgb_t sdlConsoleEngineRenderer2D::fillBackground(_rgb_t newColor) {
	_rgb_t currentColor = backColor;
	backColor = newColor;
	SDL_SetRenderDrawColor(consoleRenderer,backColor.r,backColor.g,backColor.b,backColor.a);
	SDL_RenderClear(consoleRenderer);
}

void sdlConsoleEngineRenderer2D::drawText(const char *text, int x, int y) {
	SDL_Color textColor = {255,255,255,0};
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

void sdlConsoleEngineRenderer2D::update() {
	SDL_RenderPresent(consoleRenderer);
}