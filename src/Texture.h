#pragma once

#include <glbinding/gl/gl.h>
#include <glbinding/binding.h>
#include <iostream>

#include "Image.h"

namespace GameEngine {
	class Texture2D {
	private:
		std::unique_ptr<Image> internalImage;
		gl::GLuint ID;
		gl::GLenum Wrap_S, Wrap_T, Filter_Min, Filter_Max, imageFormat, textureFormat;
	public:
		Texture2D();
		void generate(std::unique_ptr<Image>& image);
		void bind() const;
		gl::GLuint* getId();
	};
	class TextureCube {
	private:
		std::vector<std::unique_ptr<Image>> internalFaces;
		gl::GLuint ID;
		gl::GLenum Wrap_S, Wrap_T, Filter_Min, Filter_Max, imageFormat, textureFormat;
	public:
		TextureCube();
		void generate(std::vector<std::unique_ptr<Image>>& faces);
		gl::GLuint* getId();
		void bind() const;
	};
}