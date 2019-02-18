#pragma once

#include <glbinding/gl/gl.h>
#include <glbinding/binding.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace GameEngine {
	class Shader {
	public:
		Shader();
		void compile(const gl::GLchar* vertex, const gl::GLchar* fragment, const gl::GLchar* geomentry = nullptr);
		void use();
		void setBool(const std::string &name, gl::GLboolean value);
		void setInt(const std::string &name, gl::GLint value);
		void setFloat(const std::string &name, gl::GLfloat value);
		void setMat4(const std::string &name, glm::mat4& value);
		void setVec3(const std::string &name, glm::vec3& value);
		void setVec3(const std::string &name, gl::GLfloat x, gl::GLfloat y, gl::GLfloat z);
		void setVec2(const std::string &name, glm::vec2& value);
		void setVec2(const std::string &name, gl::GLfloat x, gl::GLfloat y);
		void setVec4(const std::string &name, glm::vec4& value);
		void setVec4(const std::string &name, gl::GLfloat x, gl::GLfloat y, gl::GLfloat z, gl::GLfloat w);
		gl::GLuint getId() const;
	private:
		gl::GLuint ID;
		void checkErrors(gl::GLuint index, const std::string& type);
	};
}