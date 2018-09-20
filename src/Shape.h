#pragma once
#include <glbinding/gl/gl.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Image.h"
#include "Screen.h"

namespace GameEngine {
	class Shape {
	public:
		Shape(Screen* screen);
		virtual ~Shape();
		virtual void draw();
		gl::GLuint shaderProgram, vao, vbo, ebo, vertexShader, fragShader, tex;
	protected:
		const char* vertexSource, *fragSource;
		Screen* screen;
	};
	class Sprite : public Shape {
	public:
		Sprite(float x, float y, float width, float height, std::string imgpath, Screen* screen);
		~Sprite();
		void rotate(float degrees);
		void translate(float dx, float dy);
		void draw() override;
	private:
		float x, y, width, height;
		Image* texture;
		gl::GLint posAttrib, texAttrib;
	};
}