#include <sdlConsoleEngine.h>
#include <SDL_ttf.h>

#include <sstream>

using namespace std;

class myDerivativeEngine : public sdlConsoleEngine2D {
public:
	myDerivativeEngine(int,int);

	void onLoop(double fDeltaTime) override;
};

myDerivativeEngine::myDerivativeEngine(int w, int h) : sdlConsoleEngine2D(w,h) {
	setMaxFPS(60);
}

void myDerivativeEngine::onLoop(double fDeltaTime) {
	renderer.setForeColor(COLOR_RED);

	renderer.fillTriangle({120,150},{250,80},{200,300},COLOR_RED);

	renderer.setForeColor(COLOR_GREY);
	stringstream fpsStringStream;
	fpsStringStream << "FPS: " << getFPS();
	renderer.drawText(fpsStringStream.str().c_str(),10,10);
}

int main() {
	myDerivativeEngine testEngine(640,480);
	return testEngine.onExecute();	
}