#ifndef _SHAPE_TRIANGLE_H
#define _SHAPE_TRIANGLE_H

#include "shape.h"

class Triangle : public Shape {
private:
    Point points[3];
    Point centroid;

public:
    Triangle();
    Triangle(sdlConsoleEngineRenderer2D *renderer);

    void setPoints(Point a, Point b, Point c);
    void rotate(double fDegrees);
    void draw() override;

private:
    void sortPoints();
    void computeCentroid();
};

#endif