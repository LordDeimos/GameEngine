#include <glbinding/gl/gl.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Image.h"

namespace GameEngine {
	class Shape {
	public:
		Shape();
		virtual ~Shape();
		virtual void draw();
		gl::GLuint shaderProgram, vao, vbo, ebo, vertexShader, fragShader, tex;
	protected:
		const char* vertexSource, *fragSource;
	};
	class Sprite : public Shape {
	public:
		Sprite(float x, float y, float width, float height, std::string imgpath, gl::GLenum index);
		~Sprite();
		void rotate(float degrees);
		void translate(float dx, float dy);
		void draw() override;
	private:
		float x, y, width, height;
		Image* texture;
		gl::GLint posAttrib, texAttrib;
		gl::GLenum index;
	};
}