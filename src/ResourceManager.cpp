
#include "ResourceManager.h"

using namespace GameEngine;
using namespace gl;

std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, TextureCube> ResourceManager::Cubes;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader* ResourceManager::getShader(const std::string& name) {
	return &Shaders[name];
}

Texture2D* ResourceManager::getTexture(const std::string& name) {
	return &Textures[name];
}

Shader* ResourceManager::loadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& gShaderFile, const std::string& name) {
	Shader shader;
	std::ifstream opener;

	std::vector<std::string> sources;
	std::stringstream s;
	for (auto file : { vShaderFile, fShaderFile, gShaderFile }) {
		if (file.size() == 0) continue;
		opener.open(file, std::ios::binary);
		if (opener.is_open()) {
			s << opener.rdbuf();
			sources.push_back(s.str());
			s.str(std::string());
		}
		opener.close();
	}

	shader.compile(sources[0].c_str(), sources[1].c_str(), (gShaderFile.size() != 0) ? sources[2].c_str() : nullptr);

	Shaders[name] = shader;
	return &Shaders[name];
}

Texture2D* ResourceManager::loadTexture(const std::string& imageFile, const std::string& name) {
	Texture2D texture;

	auto image = std::make_unique<Image>(imageFile);

	texture.generate(image);

	Textures[name] = std::move(texture);
	return &Textures[name];
}

TextureCube* ResourceManager::loadCube(std::vector<std::string>& imageFiles, const std::string& name) {
	TextureCube texture;
	std::vector<std::unique_ptr<Image>> images;
	for (auto face : imageFiles) {
		auto image = std::make_unique<Image>(face);
		images.push_back(std::move(image));
	}

	texture.generate(images);

	Cubes[name] = std::move(texture);
	return &Cubes[name];
}


void ResourceManager::clear() {
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.getId());
	// (Properly) delete all textures
	for (auto& iter : Textures)
		glDeleteTextures(1, iter.second.getId());
	for (auto& iter : Cubes)
		glDeleteTextures(1, iter.second.getId());
}