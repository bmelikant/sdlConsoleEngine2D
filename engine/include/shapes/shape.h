#ifndef _SHAPE_BASIC_H
#define _SHAPE_BASIC_H

#include <SDL.h>
#include "sdlConsoleEngineRenderer2D.h"

class Shape {
protected:
    sdlConsoleEngineRenderer2D *renderer;
    Color shapeColor;
    bool drawFilled;

public:
    Shape();
    Shape(sdlConsoleEngineRenderer2D *renderer);

    void setRenderer(sdlConsoleEngineRenderer2D *renderer);
    Color setDrawColor(Color c);
    void setFillMode(bool fill);
    bool getFillMode();

    virtual void draw() = 0;
};

#endif