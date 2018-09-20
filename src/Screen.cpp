#include "Screen.h"

using namespace GameEngine;
using namespace std;

Screen::Screen() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	window = SDL_CreateWindow("OpenGL", 100, 100, 800, 800, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);
	glbinding::Binding::initialize();
	shape = new Sprite(-0.5f, 0.5f, 1.0f, 1.0f, "stim-it.tga", this);
	shape2 = new Sprite(0.5f, -0.5f, 0.2f, 0.2f, "stim-math.tga", this);

}

Screen::Screen(const char* title, int x, int y, int width, int height) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);
	glbinding::Binding::initialize();
	shape = new Sprite(0.0f,0.0f,0.5f,0.5f,"stim-it.bmp", this);
}

int Screen::draw() {
	while (1) {
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT) break;
		}
		gl::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		gl::glClear(static_cast<gl::ClearBufferMask>(GL_COLOR_BUFFER_BIT));
		shape->draw();
		shape2->draw();
		clearCache();
		SDL_GL_SwapWindow(this->window);
	}

	delete[] shape; delete[] shape2;

	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}

gl::GLenum Screen::getFreeTexture() {
	gl::GLenum index = static_cast<gl::GLenum>(textureCache.size() + static_cast<int>(static_cast<gl::GLenum>(GL_TEXTURE0)));
	textureCache.push_back(index);
	return index;
}

void Screen::clearCache() {
	textureCache.clear();
}