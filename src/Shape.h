#pragma once
#include <glbinding/gl/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "Image.h"

namespace GameEngine {
	class Screen;
	class Shape {
	public:
		Shape(Screen* screen);
		virtual ~Shape();
		virtual void draw();
		gl::GLuint shaderProgram, vao, vbo, ebo, vertexShader, fragShader, tex;
	protected:
		const char* vertexSource;
		const char* fragSource;
		Screen* screen;
		glm::mat4 trans = glm::mat4(1.0f);
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
		gl::GLenum index;
		void compileShaders();
	};
}