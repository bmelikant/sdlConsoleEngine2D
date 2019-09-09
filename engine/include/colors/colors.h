#ifndef _COLORS_H
#define _COLORS_H

#include <SDL.h>

using Color = SDL_Color;

const Color COLOR_RED = {255,0,0,255};
const Color COLOR_GREEN = {0,255,0,255};
const Color COLOR_BLUE = {0,0,255,255};
const Color COLOR_BLACK = {0,0,0,0};
const Color COLOR_DARK_RED = {128,0,0,255};
const Color COLOR_DARK_GREEN = {0,128,0,255};
const Color COLOR_DARK_BLUE = {0,0,128,255};
const Color COLOR_GREY = {128,128,128,255};

#endif