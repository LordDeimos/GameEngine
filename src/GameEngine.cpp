// GameEngine.cpp : Defines the entry point for the application.
//

#include "GameEngine.h"

using namespace std;

int main(int argc, char** argv)
{
	GameEngine::Screen* screen = new GameEngine::Screen();
	GameEngine::Shape* shape = new GameEngine::Sprite(-0.5f, 0.5f, 1.0f, 1.0f, "stim-it.tga", screen);
	GameEngine::Shape* shape2 = new GameEngine::Sprite(0.5f, -0.5f, 0.2f, 0.2f, "stim-math.tga", screen);
	std::vector<int> myints;
	std::cout << myints.size() << std::endl;
	screen->addShape(shape);
	screen->addShape(shape2);
	return screen->draw();
}