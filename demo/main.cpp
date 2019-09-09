#include <sdlConsoleEngine.h>
#include <SDL_ttf.h>

#include <sstream>
#include <cmath>

#include "shapes/triangle.h"

using namespace std;

class myDerivativeEngine : public sdlConsoleEngine2D {
private:
	Triangle *t;
	bool rotating;

public:
	myDerivativeEngine(int,int);

	bool onUserInit() override;
	void onUserLoop(double fDeltaTime) override;
	void onUserEvent(SDL_Event *event) override;
};

myDerivativeEngine::myDerivativeEngine(int w, int h) : sdlConsoleEngine2D(w,h) {

}

bool myDerivativeEngine::onUserInit() {
	// try to set the font for rendering
	renderer->setFont("./resources/fonts/DejaVuSans-ExtraLight.ttf",14);
	t = shapeFactory->getShape<Triangle>();

	t->setPoints({120,150},{250,80},{200,300});
	t->setDrawColor(COLOR_GREEN);
	setMaxFPS(60);

	rotating = true;
	return true;
}

void myDerivativeEngine::onUserEvent(SDL_Event *event) {
	if (event->type == SDL_KEYDOWN) {
		switch (event->key.keysym.scancode) {
			case SDL_SCANCODE_LEFT:
				t->setFillMode(!t->getFillMode());
				break;
			case SDL_SCANCODE_RIGHT:
				t->setFillMode(!t->getFillMode());
				break;
			case SDL_SCANCODE_A:
				t->rotate(0.5f);
				break;
			case SDL_SCANCODE_D:
				t->rotate(-0.5f);
				break;
			case SDL_SCANCODE_SPACE:
				rotating = !rotating;
				break;
		}
	}
}

void myDerivativeEngine::onUserLoop(double fDeltaTime) {
	// draw a spinny triangle
	if (rotating) {
		//t->rotate(0.5f/fDeltaTime);
	}

	t->draw();

	renderer->setForeColor(COLOR_GREY);
	stringstream fpsStringStream;
	fpsStringStream << "FPS: " << getFPS();
	renderer->drawText(fpsStringStream.str().c_str(),10,10);
}

int main() {
	myDerivativeEngine testEngine(640,480);
	return testEngine.onExecute();	
}