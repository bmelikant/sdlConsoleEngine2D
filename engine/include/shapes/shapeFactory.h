#ifndef _SHAPE_FACTORY_H
#define _SHAPE_FACTORY_H

#include "../sdlConsoleEngineRenderer2D.h"
#include "shapes/shape.h"

class ShapeFactory {
private:
    sdlConsoleEngineRenderer2D *renderer;

public:
    ShapeFactory(sdlConsoleEngineRenderer2D *renderer);

    template <class T>
    T *getShape();
};

template <class T>
T *ShapeFactory::getShape() {
    T *newShape = new T();
    newShape->setRenderer(this->renderer);
    return newShape;
}

#endif