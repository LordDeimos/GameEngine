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
	shape = new Sprite(-0.5f, 0.5f, 1.0f, 1.0f, "stim-it.tga", static_cast<gl::GLenum>(GL_TEXTURE0));
	shape2 = new Sprite(0.5f, -0.5f, 0.2f, 0.2f, "stim-math.tga", static_cast<gl::GLenum>(GL_TEXTURE1));

}

Screen::Screen(const char* title, int x, int y, int width, int height) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);
	glbinding::Binding::initialize();
	shape = new Sprite(0.0f,0.0f,0.5f,0.5f,"stim-it.bmp", static_cast<gl::GLenum>(GL_TEXTURE0));
}

int Screen::draw() {
	while (1) {
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT) break;
		}
		gl::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		gl::glClear(static_cast<gl::ClearBufferMask>(GL_COLOR_BUFFER_BIT));
		//gl::glDrawElements(static_cast<gl::GLenum>(GL_TRIANGLES), 6, static_cast<gl::GLenum>(GL_UNSIGNED_INT), 0);
		shape->draw();
		shape2->draw();
		//gl::glDrawArrays(ENUMCAST(GL_TRIANGLES), 0, 3);

		SDL_GL_SwapWindow(this->window);
	}

	delete[] shape; delete[] shape2;

	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}