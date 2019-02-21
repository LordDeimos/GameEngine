
#include "Texture.h"

using namespace GameEngine;
using namespace gl;

Texture2D::Texture2D() : imageFormat(GLenum::GL_RGB), textureFormat(GLenum::GL_RGB), Wrap_S(GLenum::GL_REPEAT), Wrap_T(GLenum::GL_REPEAT), Filter_Min(GLenum::GL_LINEAR), Filter_Max(GLenum::GL_LINEAR) {
	glGenTextures(1, &this->ID);
}

void Texture2D::generate(std::unique_ptr<Image>& image) {

	if (image->hasAlpha()) {
		this->imageFormat = GLenum::GL_RGBA;
		this->textureFormat = GLenum::GL_RGBA;
	}

	glBindTexture(GLenum::GL_TEXTURE_2D, this->ID);
	glTexImage2D(GLenum::GL_TEXTURE_2D, 0, this->imageFormat, image->width, image->height, 0, this->textureFormat, GLenum::GL_UNSIGNED_BYTE, image->image);
	// Set Texture wrap and filter modes
	glTexParameteri(GLenum::GL_TEXTURE_2D, GLenum::GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GLenum::GL_TEXTURE_2D, GLenum::GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GLenum::GL_TEXTURE_2D, GLenum::GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GLenum::GL_TEXTURE_2D, GLenum::GL_TEXTURE_MAG_FILTER, this->Filter_Max);
	// Unbind texture
	glBindTexture(GLenum::GL_TEXTURE_2D, 0);
	this->internalImage = std::move(image);
}

void Texture2D::bind() const {
	glBindTexture(GLenum::GL_TEXTURE_2D, this->ID);
}

GLuint* Texture2D::getId() {
	return &(this->ID);
}

TextureCube::TextureCube() : imageFormat(GLenum::GL_RGB), textureFormat(GLenum::GL_RGB), Wrap_S(GLenum::GL_REPEAT), Wrap_T(GLenum::GL_REPEAT), Filter_Min(GLenum::GL_LINEAR), Filter_Max(GLenum::GL_LINEAR) {
	glGenTextures(1, &this->ID);
}

void TextureCube::generate(std::vector<std::unique_ptr<Image>>& faces) {
	gl::glBindTexture(gl::GLenum::GL_TEXTURE_CUBE_MAP, ID);

	for (unsigned int i = 0; i < faces.size(); i++){
		glTexImage2D(gl::GLenum::GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, gl::GLenum::GL_RGBA, faces[i]->width, faces[i]->height, 0, gl::GLenum::GL_RGBA, gl::GLenum::GL_UNSIGNED_BYTE, faces[i]->image);
	}
	glTexParameteri(gl::GLenum::GL_TEXTURE_CUBE_MAP, gl::GLenum::GL_TEXTURE_MIN_FILTER, gl::GLenum::GL_LINEAR);
	glTexParameteri(gl::GLenum::GL_TEXTURE_CUBE_MAP, gl::GLenum::GL_TEXTURE_MAG_FILTER, gl::GLenum::GL_LINEAR);
	glTexParameteri(gl::GLenum::GL_TEXTURE_CUBE_MAP, gl::GLenum::GL_TEXTURE_WRAP_S, gl::GLenum::GL_CLAMP_TO_EDGE);
	glTexParameteri(gl::GLenum::GL_TEXTURE_CUBE_MAP, gl::GLenum::GL_TEXTURE_WRAP_T, gl::GLenum::GL_CLAMP_TO_EDGE);
	glTexParameteri(gl::GLenum::GL_TEXTURE_CUBE_MAP, gl::GLenum::GL_TEXTURE_WRAP_R, gl::GLenum::GL_CLAMP_TO_EDGE);
	this->internalFaces = std::move(faces);
};

GLuint* TextureCube::getId() {
	return &(this->ID);
}

void TextureCube::bind() const {
	glBindTexture(GLenum::GL_TEXTURE_CUBE_MAP, this->ID);
}