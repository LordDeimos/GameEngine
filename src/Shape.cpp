#include "Shape.h"
#include "Screen.h"

#undef GL_ARRAY_BUFFER
#undef GL_STATIC_DRAW
#undef GL_ELEMENT_ARRAY_BUFFER
#undef GL_VERTEX_SHADER
#undef GL_FRAGMENT_SHADER
#undef GL_COMPILE_STATUS
#undef GL_FLOAT
#undef GL_TEXTURE_2D
#undef GL_TEXTURE_WRAP_S
#undef GL_CLAMP_TO_EDGE
#undef GL_TEXTURE_WRAP_T
#undef GL_TEXTURE_MIN_FILTER
#undef GL_TEXTURE_MAG_FILTER
#undef GL_LINEAR
#undef GL_RGBA
#undef GL_UNSIGNED_BYTE
#undef GL_UNSIGNED_INT
#undef GL_TRIANGLES
#undef GL_TEXTURE0

using namespace GameEngine;
using namespace gl;

Shape::Shape(Screen* screen) {
	this->screen = screen;
}

Shape::~Shape() {
}

void Shape::draw() {}

Sprite::Sprite(float x, float y, float width, float height, std::string imgpath, Screen* screen) : Shape(screen), x(x), y(y), width(width), height(height) {
	
	vertexSource = R"glsl(
		#version 150 core
		in vec2 texcoord;
		in vec2 position;
		out vec2 Texcoord;
		//uniform mat4 transform;
		void main(){
			Texcoord = texcoord;
			gl_Position = vec4(position, 0.0, 1.0);
		})glsl";
	fragSource = R"glsl(
		#version 150 core
		in vec2 Texcoord;
		out vec4 outColour;
		uniform sampler2D sprite;
		void main(){
			outColour = texture(sprite, Texcoord);
		})glsl";

	glGenVertexArrays(1, &vao);
	gl::glBindVertexArray(vao);

	GLfloat vertices[] = {
		//  Position      Texcoords
			x,y, 0.0f, 0.0f, // Top-left
			x+width,y, 1.0f, 0.0f, // Top-right
			x+width, y-height, 1.0f, 1.0f, // Bottom-right
			x, y-height, 0.0f, 1.0f  // Bottom-left
	};
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenBuffers(1, &vbo);
	gl::glBindBuffer(GLenum::GL_ARRAY_BUFFER, vbo);
	gl::glBufferData(GLenum::GL_ARRAY_BUFFER, sizeof(vertices), vertices, GLenum::GL_STATIC_DRAW);

	gl::glGenBuffers(1, &ebo);
	gl::glBindBuffer(GLenum::GL_ELEMENT_ARRAY_BUFFER, ebo);
	gl::glBufferData(GLenum::GL_ELEMENT_ARRAY_BUFFER,
		sizeof(elements), elements, GLenum::GL_STATIC_DRAW);

	vertexShader = glCreateShader(GLenum::GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint status;
	glGetShaderiv(vertexShader, GLenum::GL_VERTEX_SHADER, &status);
	if (status != 1) {
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		OutputDebugString(buffer);
		OutputDebugString("\n");
	}

	fragShader = glCreateShader(GLenum::GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GLenum::GL_COMPILE_STATUS, &status);
	if (status != 1) {
		char buffer[512];
		glGetShaderInfoLog(fragShader, 512, NULL, buffer);
		OutputDebugString(buffer);
		OutputDebugString("\n");
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glBindFragDataLocation(shaderProgram, 0, "outColour");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GLenum::GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GLenum::GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));

	texture = new TgaImage(imgpath);
}

Sprite::~Sprite() {

	gl::glDeleteTextures(1, &tex);

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);
}

void Sprite::draw() {
	gl::GLenum index = screen->getFreeTexture();
	int id = (int)index - (int)GLenum::GL_TEXTURE0;
	glBindVertexArray(vao);
	glActiveTexture(index);
	glBindTexture(GLenum::GL_TEXTURE_2D, tex);
	glTexImage2D(GLenum::GL_TEXTURE_2D, 0, GLenum::GL_RGBA, texture->width, texture->height, 0, GLenum::GL_RGBA, GLenum::GL_UNSIGNED_BYTE, texture->image);
	glUniform1i(glGetUniformLocation(shaderProgram, "sprite"), id);

	glTexParameteri(GLenum::GL_TEXTURE_2D, GLenum::GL_TEXTURE_WRAP_S, GLenum::GL_CLAMP_TO_EDGE);
	glTexParameteri(GLenum::GL_TEXTURE_2D, GLenum::GL_TEXTURE_WRAP_T, GLenum::GL_CLAMP_TO_EDGE);
	glTexParameteri(GLenum::GL_TEXTURE_2D, GLenum::GL_TEXTURE_MIN_FILTER, GLenum::GL_LINEAR);
	glTexParameteri(GLenum::GL_TEXTURE_2D, GLenum::GL_TEXTURE_MAG_FILTER, GLenum::GL_LINEAR);
	gl::glDrawElements(GLenum::GL_TRIANGLES, 6, GLenum::GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Sprite::rotate(float degrees) {
	GLint transform = glGetUniformLocation(shaderProgram, "transform");
}

void Sprite::translate(float dx, float dy) {
	//Implemet Matrices
}