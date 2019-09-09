#include "shapes/triangle.h"

Triangle::Triangle() {
    points[0] = {0,0};
    points[1] = {0,0};
    points[2] = {0,0};
}

void Triangle::setPoints(Point a, Point b, Point c) {
    points[0] = a;
    points[1] = b;
    points[2] = c;
    sortPoints();
    computeCentroid();
}

void Triangle::sortPoints() {
    if (points[0].y > points[1].y) {
        Point temp = points[1];
        points[1] = points[0];
        points[0] = temp;
        sortPoints();
    } else if (points[1].y > points[2].y) {
        Point temp = points[2];
        points[2] = points[1];
        points[1] = temp;
        sortPoints();
    }
}

void Triangle::draw() {
    if (this->drawFilled) {
        this->renderer->fillTriangle(points[0],points[1],points[2],this->shapeColor);
    } else {
        this->renderer->drawTriangle(points[0],points[1],points[2],this->shapeColor);
    }
}

void Triangle::rotate(double fDegrees) {
    for (int i = 0; i < 3; i++) {
        // translate point to centroid, rotate, then re-zero the origin
        points[i] -= centroid;
        points[i].rotate((float) fDegrees);
        points[i] += centroid;
    }
}

void Triangle::computeCentroid() {
    this->centroid = {
        ((points[0].x + points[1].x + points[2].x) / 3),
        ((points[0].y + points[1].y + points[2].y) / 3)
    };
}