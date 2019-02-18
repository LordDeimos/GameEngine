#pragma once
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <glbinding/gl/gl.h>
#include <glbinding/binding.h>

#include "Shader.h"
#include "Texture.h"
#include "Image.h"

namespace GameEngine {
	static class ResourceManager
	{
	public:
		static Shader* getShader(const std::string& name);
		static Texture2D* getTexture(const std::string& name);
		static Shader* loadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, const std::string& name);
		static Texture2D* loadTexture(const std::string& imageFile, const std::string& name);
		static TextureCube* loadCube(std::vector<std::string>& imageFiles, const std::string& name);
		static void clear();
	private:
		ResourceManager();
		static std::map<std::string, Shader> Shaders;
		static std::map<std::string, Texture2D> Textures;
		static std::map<std::string, TextureCube> Cubes;
	};
}