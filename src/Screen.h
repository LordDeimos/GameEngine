#pragma once
#include <glbinding/gl/gl.h>
#include <glbinding/binding.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Image.h"

namespace GameEngine {
	class Shape;
	class Screen {
	public:
		Screen();
		Screen(const char* title, int x, int y, int width, int height);
		~Screen();
		int draw();
		gl::GLenum getFreeTexture();
		void clearCache();
		void addShape(Shape* shape);
	private:
		SDL_Window* window;
		SDL_GLContext context;
		SDL_Event windowEvent;
		std::vector<Shape*> shapes;
		std::vector<gl::GLenum> textureCache;
	};
}