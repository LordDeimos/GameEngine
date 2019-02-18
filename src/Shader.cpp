

#include "Shader.h"

#define BUFFER_SIZE 1024

using namespace GameEngine;
using namespace gl;

Shader::Shader() {}

GLuint Shader::getId() const {
	return this->ID;
}

void Shader::compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource) {
	
	GLuint sVertex, sFragment, gShader;
	// Vertex Shader
	sVertex = glCreateShader(GLenum::GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkErrors(sVertex, "Vertex");
	// Fragment Shader
	sFragment = glCreateShader(GLenum::GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkErrors(sFragment, "Fragment");
	// If geometry shader source code is given, also compile geometry shader
	if (geometrySource != nullptr)
	{
		gShader = glCreateShader(GLenum::GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkErrors(gShader, "Geometry");
	}
	// Shader Program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);
	if (geometrySource != nullptr)
		glAttachShader(this->ID, gShader);
	glLinkProgram(this->ID);
	checkErrors(this->ID, "Program");
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr)
		glDeleteShader(gShader);
}

void Shader::use() {
	glUseProgram(ID);
}


void Shader::checkErrors(gl::GLuint index, const std::string& type) {
	GLint success;
	GLchar log[BUFFER_SIZE];
	
	std::stringstream logger;
	logger << "Error: " << type;

	if (type == "Program") {
		glGetProgramiv(index, GLenum::GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(index, BUFFER_SIZE, nullptr, log);
			logger << "Link Error - " << log;
		}
	}
	else {
		logger << " Shader ";
		glGetShaderiv(index, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(index, BUFFER_SIZE, NULL, log);
			logger << "Compile Error - " << log;
		}
	}
	if (!success)
		std::cout << logger.str() << std::endl;
}

void Shader::setBool(const std::string &name, GLboolean value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, GLint value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, GLfloat value) {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, glm::vec3& value)  {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, GLfloat x, GLfloat y, GLfloat z) {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec2(const std::string &name, glm::vec2& value) {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec2(const std::string &name, GLfloat x, GLfloat y) {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec4(const std::string &name, glm::vec4& value) {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string &name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}