// GameEngine.cpp : Defines the entry point for the application.
//

#include "GameEngine.h"

using namespace std;

int main(int argc, char** argv)
{
	GameEngine::Screen* screen = new GameEngine::Screen();
	return screen->draw();
}