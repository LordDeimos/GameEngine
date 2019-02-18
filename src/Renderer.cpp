#include "Renderer.h"

using namespace GameEngine;

gl::GLfloat Renderer::frameVertices[] = {
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
};

Renderer::Renderer() {
	gl::glGenFramebuffers(1, &frameBuffer);
	gl::glBindFramebuffer(gl::GLenum::GL_FRAMEBUFFER, frameBuffer);

	gl::glGenTextures(1, &colourBuffer);
	gl::glBindTexture(gl::GLenum::GL_TEXTURE_2D, colourBuffer);
	gl::glTexImage2D(gl::GLenum::GL_TEXTURE_2D, 0, gl::GLenum::GL_RGB, 800, 600, 0, gl::GLenum::GL_RGB, gl::GLenum::GL_UNSIGNED_BYTE, nullptr);
	gl::glTexParameteri(gl::GLenum::GL_TEXTURE_2D, gl::GLenum::GL_TEXTURE_MIN_FILTER, gl::GLenum::GL_LINEAR);
	gl::glTexParameteri(gl::GLenum::GL_TEXTURE_2D, gl::GLenum::GL_TEXTURE_MAG_FILTER, gl::GLenum::GL_LINEAR);
	gl::glBindTexture(gl::GLenum::GL_TEXTURE_2D, 0);

	gl::glFramebufferTexture2D(gl::GLenum::GL_FRAMEBUFFER, gl::GLenum::GL_COLOR_ATTACHMENT0, gl::GLenum::GL_TEXTURE_2D, colourBuffer, 0);

	gl::glGenRenderbuffers(1, &renderBuffer);
	gl::glBindRenderbuffer(gl::GLenum::GL_RENDERBUFFER, renderBuffer);
	gl::glRenderbufferStorage(gl::GLenum::GL_RENDERBUFFER, gl::GLenum::GL_DEPTH24_STENCIL8, 800, 600);
	gl::glBindRenderbuffer(gl::GLenum::GL_RENDERBUFFER, 0);

	gl::glFramebufferRenderbuffer(gl::GLenum::GL_FRAMEBUFFER, gl::GLenum::GL_DEPTH_STENCIL_ATTACHMENT, gl::GLenum::GL_RENDERBUFFER, renderBuffer);

	if (gl::glCheckFramebufferStatus(gl::GLenum::GL_FRAMEBUFFER) != gl::GLenum::GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "Error: Framebuffer not Complete" << std::endl;
	}
	gl::glBindFramebuffer(gl::GLenum::GL_FRAMEBUFFER, 0);

	gl::glGenVertexArrays(1, &frameVAO);
	gl::glBindVertexArray(frameVAO);
	gl::glGenBuffers(1, &frameVBO);
	gl::glBindBuffer(gl::GLenum::GL_ARRAY_BUFFER, frameVBO);
	gl::glBufferData(gl::GLenum::GL_ARRAY_BUFFER, sizeof(frameVertices), frameVertices, gl::GLenum::GL_STATIC_DRAW);
	gl::glVertexAttribPointer(0, 2, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 4 * sizeof(float), (void*)0);
	gl::glEnableVertexAttribArray(0);
	gl::glVertexAttribPointer(1, 2, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	gl::glEnableVertexAttribArray(1);

	frameShader = ResourceManager::loadShader("../src/Shaders/framebuffer.vs.glsl", "../src/Shaders/framebuffer.fs.glsl", "", "frameBuffer");
}

void Renderer::set() {
	gl::glBindFramebuffer(gl::GLenum::GL_FRAMEBUFFER, frameBuffer);
	gl::glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	gl::glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT | gl::ClearBufferMask::GL_DEPTH_BUFFER_BIT /*| gl::ClearBufferMask::GL_STENCIL_BUFFER_BIT*/);
	gl::glEnable(gl::GLenum::GL_DEPTH_TEST);
}

void Renderer::unset() {
	gl::glBindFramebuffer(gl::GLenum::GL_FRAMEBUFFER, 0);
	gl::glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	gl::glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT);
	frameShader->use();
	gl::glBindVertexArray(frameVAO);
	gl::glDisable(gl::GLenum::GL_DEPTH_TEST);
	gl::glBindTexture(gl::GLenum::GL_TEXTURE_2D, colourBuffer);
	gl::glDrawArrays(gl::GLenum::GL_TRIANGLES, 0, 6);
}

void Renderer::render(Shader* shader, Camera* camera, Model* model) {
	shader->use();
	shader->setMat4("projection", camera->perspective());
	shader->setMat4("view", camera->view());
	shader->setVec3("viewPos", camera->position());
	shader->setFloat("shininess", 32.0f);
	/*for (int i = 0; i < 4; i++) {
		std::stringstream s;
		s << "pointLights[" << i << "].";
		modelShaders->setVec3(s.str() + "position", pointLightPositions[i]);
		modelShaders->setVec3(s.str() + "ambient", 0.05f, 0.05f, 0.05f);
		modelShaders->setVec3(s.str() + "diffuse", 0.8f, 0.8f, 0.8f);
		modelShaders->setVec3(s.str() + "specular", 1.0f, 1.0f, 1.0f);
		modelShaders->setFloat(s.str() + "constant", 1.0f);
		modelShaders->setFloat(s.str() + "linear", 0.09);
		modelShaders->setFloat(s.str() + "quadratic", 0.032);
	}*/
	model->Draw(shader);
}