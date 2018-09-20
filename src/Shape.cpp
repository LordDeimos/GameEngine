#include "Shape.h"

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
	glBindVertexArray(vao);

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
	glBindBuffer(static_cast<gl::GLenum>(GL_ARRAY_BUFFER), vbo);
	glBufferData(static_cast<gl::GLenum>(GL_ARRAY_BUFFER), sizeof(vertices), vertices, static_cast<gl::GLenum>(GL_STATIC_DRAW));

	glGenBuffers(1, &ebo);
	glBindBuffer(static_cast<gl::GLenum>(GL_ELEMENT_ARRAY_BUFFER), ebo);
	glBufferData(static_cast<gl::GLenum>(GL_ELEMENT_ARRAY_BUFFER),
		sizeof(elements), elements, static_cast<gl::GLenum>(GL_STATIC_DRAW));

	vertexShader = glCreateShader(static_cast<gl::GLenum>(GL_VERTEX_SHADER));
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint status;
	glGetShaderiv(vertexShader, static_cast<gl::GLenum>(GL_VERTEX_SHADER), &status);
	if (status != 1) {
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
		OutputDebugString(buffer);
		OutputDebugString("\n");
	}

	fragShader = glCreateShader(GLenum::GL_FRAGMENT_SHADER));
	glShaderSource(fragShader, 1, &fragSource, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GLenum::GL_COMPILE_STATUS), &status);
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
	glVertexAttribPointer(posAttrib, 2, static_cast<gl::GLenum>(GL_FLOAT), GL_FALSE, 4 * sizeof(GLfloat), 0);

	texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, static_cast<gl::GLenum>(GL_FLOAT), GL_FALSE, 4 * sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));

	texture = new TgaImage(imgpath);
	if (!texture->ok) return;

	glTexParameteri(static_cast<gl::GLenum>(GL_TEXTURE_2D), static_cast<gl::GLenum>(GL_TEXTURE_WRAP_S), static_cast<gl::GLenum>(GL_CLAMP_TO_EDGE));
	glTexParameteri(static_cast<gl::GLenum>(GL_TEXTURE_2D), static_cast<gl::GLenum>(GL_TEXTURE_WRAP_T), static_cast<gl::GLenum>(GL_CLAMP_TO_EDGE));
	glTexParameteri(static_cast<gl::GLenum>(GL_TEXTURE_2D), static_cast<gl::GLenum>(GL_TEXTURE_MIN_FILTER), static_cast<gl::GLenum>(GL_LINEAR));
	glTexParameteri(static_cast<gl::GLenum>(GL_TEXTURE_2D), static_cast<gl::GLenum>(GL_TEXTURE_MAG_FILTER), static_cast<gl::GLenum>(GL_LINEAR));
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
	int id = (int)index - (int)GL_TEXTURE0;
	glBindVertexArray(vao);
	glActiveTexture(index);
	glBindTexture(static_cast<gl::GLenum>(GL_TEXTURE_2D), tex);
	glTexImage2D(static_cast<gl::GLenum>(GL_TEXTURE_2D), 0, static_cast<gl::GLenum>(GL_RGBA), texture->width, texture->height, 0, static_cast<gl::GLenum>(GL_RGBA), static_cast<gl::GLenum>(GL_UNSIGNED_BYTE), texture->image);
	glUniform1i(glGetUniformLocation(shaderProgram, "sprite"), id);

	glTexParameteri(static_cast<gl::GLenum>(GL_TEXTURE_2D), static_cast<gl::GLenum>(GL_TEXTURE_WRAP_S), static_cast<gl::GLenum>(GL_CLAMP_TO_EDGE));
	glTexParameteri(static_cast<gl::GLenum>(GL_TEXTURE_2D), static_cast<gl::GLenum>(GL_TEXTURE_WRAP_T), static_cast<gl::GLenum>(GL_CLAMP_TO_EDGE));
	glTexParameteri(static_cast<gl::GLenum>(GL_TEXTURE_2D), static_cast<gl::GLenum>(GL_TEXTURE_MIN_FILTER), static_cast<gl::GLenum>(GL_LINEAR));
	glTexParameteri(static_cast<gl::GLenum>(GL_TEXTURE_2D), static_cast<gl::GLenum>(GL_TEXTURE_MAG_FILTER), static_cast<gl::GLenum>(GL_LINEAR));
	gl::glDrawElements(static_cast<gl::GLenum>(GL_TRIANGLES), 6, static_cast<gl::GLenum>(GL_UNSIGNED_INT), 0);
	glBindVertexArray(0);
}

void Sprite::rotate(float degrees) {
	GLint transform = glGetUniformLocation(shaderProgram, "transform");
}

void Sprite::translate(float dx, float dy) {
	//Implemet Matrices
}