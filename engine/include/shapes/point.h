#ifndef _POINT_H
#define _POINT_H

#include <cmath>

struct POINT {
    float x;
    float y;

    POINT& operator+=(POINT add) {
        x += add.x;
        y += add.y;
        return *this;
    }

    POINT& operator-=(POINT subtract) {
        x -= subtract.x;
        y -= subtract.y;
        return *this;
    }

    POINT& operator=(POINT point) {
        x = point.x;
        y = point.y;
        return *this;
    }

    void rotate(float fDegrees) {
        x = (cos(fDegrees)*x)-(sin(fDegrees)*y);
        y = (cos(fDegrees)*y)+(sin(fDegrees)*x);
    }
};

using Point = struct POINT;

#endif