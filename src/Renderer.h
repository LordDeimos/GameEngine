#include <glbinding/gl/gl.h>
#include <glbinding/binding.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "ResourceManager.h"

namespace GameEngine {
	class Renderer {
	private:
		gl::GLuint frameBuffer, colourBuffer, renderBuffer, frameVAO, frameVBO;
		static gl::GLfloat frameVertices[];
		Shader* frameShader;
	public:
		Renderer();
		void set();
		void unset();
		void render(Shader* shader, Camera* camera, Model* model);
	};
}