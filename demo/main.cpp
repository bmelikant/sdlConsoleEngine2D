#include <sdlConsoleEngine.h>
#include <SDL_ttf.h>

#include <sstream>
#include <cmath>

using namespace std;

class Triangle {
public:
	Point a,b,c, centroid;

	Triangle();
	Triangle(Point a, Point b, Point c);

	void setPoints(Point a, Point b, Point c);
	void rotate(float fDegrees);

private:

	void calculateCentroid();
};

Triangle::Triangle() {
	this->a = {0,0};
	this->b = {0,0};
	this->c = {0,0};
}

Triangle::Triangle(Point a, Point b, Point c) {
	this->a = a;
	this->b = b;
	this->c = c;
	calculateCentroid();
}

void Triangle::setPoints(Point a, Point b, Point c) {
	this->a = a;
	this->b = b;
	this->c = c;
	calculateCentroid();
}

void applyRotation(Point &rotate, float fDegrees) {
	Point newPoint = {
		(cos(fDegrees)*rotate.x)-(sin(fDegrees)*rotate.y),
		(cos(fDegrees)*rotate.y)+(sin(fDegrees)*rotate.x)
	};
	rotate = newPoint;
}

void addPoint(Point &a, Point b) {
	a.x += b.x;
	a.y += b.y;
}

void subtractPoint(Point &a, Point b) {
	a.x -= b.x;
	a.y -= b.y;
}

// rotate each point of the triangle by the given amount
void Triangle::rotate(float fDegrees) {
	// translate origin to centroid
	subtractPoint(a,centroid);
	subtractPoint(b,centroid);
	subtractPoint(c,centroid);

	// apply rotation matrix
	applyRotation(a,fDegrees);
	applyRotation(b,fDegrees);
	applyRotation(c,fDegrees);

	// translate back to world space
	addPoint(a,centroid);
	addPoint(b,centroid);
	addPoint(c,centroid);
}

void Triangle::calculateCentroid() {
	centroid = {
		(a.x + b.x + c.x) / 3,
		(a.y + b.y + c.y) / 3
	};
}

class myDerivativeEngine : public sdlConsoleEngine2D {
private:
	Triangle t;

public:
	myDerivativeEngine(int,int);

	void onLoop(double fDeltaTime) override;
	void onEvent(SDL_Event *event) override;
};

myDerivativeEngine::myDerivativeEngine(int w, int h) : sdlConsoleEngine2D(w,h) {
	t.setPoints({120,150},{250,80},{200,300});
	setMaxFPS(60);
}

void myDerivativeEngine::onEvent(SDL_Event *event) {

}

void myDerivativeEngine::onLoop(double fDeltaTime) {
	t.rotate(0.5f/fDeltaTime);
	renderer.setForeColor(COLOR_RED);
	renderer.fillTriangle(t.a,t.b,t.c,COLOR_RED);

	renderer.setForeColor(COLOR_GREY);
	stringstream fpsStringStream;
	fpsStringStream << "FPS: " << getFPS();
	renderer.drawText(fpsStringStream.str().c_str(),10,10);
}

int main() {
	myDerivativeEngine testEngine(640,480);
	return testEngine.onExecute();	
}