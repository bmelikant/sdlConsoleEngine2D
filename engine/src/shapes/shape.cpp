#include "shapes/shape.h"

Shape::Shape() {
    this->drawFilled = false;
    this->shapeColor = COLOR_BLACK;
}

Shape::Shape(sdlConsoleEngineRenderer2D *renderer) : Shape() {
    this->renderer = renderer;
}

void Shape::setRenderer(sdlConsoleEngineRenderer2D *renderer) {
    this->renderer = renderer;
}

Color Shape::setDrawColor(Color c) {
    Color temp = this->shapeColor;
    this->shapeColor = c;
    return temp;
}

void Shape::setFillMode(bool fill) {
    this->drawFilled = fill;
}

bool Shape::getFillMode() {
    return this->drawFilled;
}