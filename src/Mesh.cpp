#include "Mesh.h"

using namespace GameEngine;
using namespace gl;


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures) : vertices(vertices), indices(indices), textures(textures){
	setupMesh();
}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GLenum::GL_ARRAY_BUFFER, vbo);

	glBufferData(GLenum::GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GLenum::GL_STATIC_DRAW);

	glBindBuffer(GLenum::GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GLenum::GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GLenum::GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GLenum::GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GLenum::GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GLenum::GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(Shader* shader) {
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GLenum::GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);

		shader->setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GLenum::GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GLenum::GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(vao);
	glDrawElements(GLenum::GL_TRIANGLES, indices.size(), GLenum::GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}