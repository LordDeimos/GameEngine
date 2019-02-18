#pragma once
#include <glbinding/gl/gl.h>
#include <glbinding/binding.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

namespace GameEngine {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct Texture {
		gl::GLuint id;
		std::string type;
		std::string path;
	};

	class Mesh {
	public:
		std::vector<Vertex> vertices;
		std::vector<gl::GLuint> indices;
		std::vector<Texture> textures;
		Mesh(std::vector<Vertex> vertices, std::vector<gl::GLuint> indices, std::vector<Texture> textures);
		void Draw(Shader* shader);
	private:
		gl::GLuint vao, vbo, ebo;
		void setupMesh();
	};
}