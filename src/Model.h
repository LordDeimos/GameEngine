#pragma once
#include <glbinding/gl/gl.h>
#include <glbinding/binding.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "ResourceManager.h"
#include "Mesh.h"

namespace GameEngine {
	class Model
	{
	public:
		Model(std::string path);
		void Draw(Shader* shader);
		void scale(float factor);
		void position(float x, float y, float z);
		void position(glm::vec3 position);
		void reset();
	private:
		std::vector<Mesh> meshes;
		std::vector<Texture> textureCache;
		std::string directory;
		glm::mat4 model = glm::mat4(1.0f);
		void loadModel(std::string path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	};
}