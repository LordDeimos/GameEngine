
#include "GameEngine.h"

using namespace GameEngine;

gl::GLuint vao, lightVao, vbo, fbo;

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

float voxelPoints[] = {
	//0.0f,0.0f,0.0f,//Center
	0.0f,0.0f,-0.5f,//Front
	0.0f,0.0f,0.5f,//Back
	-0.5f,0.0f,0.0f,//Left
	0.5f,0.0f,0.0f,//Right
	0.0f,-0.5f,0.0f,//Bottom
	0.0f,0.5f,0.0f,//Top
};

float voxelFaces[] = {0,1,2,3,4,5};

std::vector<gl::GLfloat> voxelVertices = {
	-0.5f, -0.5f, -0.5f,//0
	 0.5f, -0.5f, -0.5f,//1
	 0.5f,  0.5f, -0.5f,//2
	-0.5f,  0.5f, -0.5f,//3
	-0.5f, -0.5f,  0.5f,//4
	 0.5f, -0.5f,  0.5f,//5
	 0.5f,  0.5f,  0.5f,//6
	-0.5f,  0.5f,  0.5f,//7
};

std::vector<gl::GLuint> voxelIndices = {
	0,2,1,2,0,3,//Back
	4,5,6,6,7,4,//Front
	7,3,0,0,4,7,//Left
	6,1,2,1,6,5,//Right
	0,1,5,5,4,0,//Bottom
	3,6,2,6,3,7 //Top
};

gl::GLuint voxelVAO, voxelVBO, voxelEBO;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool processInput(SDL_Event& windowEvent, uint32_t dt) {
	bool loop = true;
	while (SDL_PollEvent(&windowEvent)) {
		if (windowEvent.type == SDL_QUIT) loop = false;
		else if (windowEvent.type == SDL_KEYDOWN) {
			switch (windowEvent.key.keysym.sym) {
			case SDLK_w:
				camera.move(Camera::Direction::UP, dt);
				break;
			case SDLK_s:
				camera.move(Camera::Direction::DOWN, dt);
				break;
			case SDLK_a:
				camera.move(Camera::Direction::LEFT, dt);
				break;
			case SDLK_d:
				camera.move(Camera::Direction::RIGHT, dt);
				break;
			case SDLK_ESCAPE:
				loop = false;
				break;
			}
		}
		else if (windowEvent.type == SDL_MOUSEMOTION) {
			camera.look(windowEvent.motion.xrel, windowEvent.motion.yrel);
		}
		else if (windowEvent.type == SDL_MOUSEWHEEL) {
			camera.zoom(windowEvent.wheel.y);
		}
	}
	return loop;
}


int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_Window* window;
	SDL_GLContext context;
	SDL_Event windowEvent;
	window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);
	glbinding::Binding::initialize();
	gl::glEnable(gl::GLenum::GL_DEPTH_TEST);
	gl::glDepthFunc(gl::GLenum::GL_LESS);
	gl::glEnable(gl::GLenum::GL_BLEND);
	gl::glBlendFunc(gl::GLenum::GL_SRC_ALPHA, gl::GLenum::GL_ONE_MINUS_SRC_ALPHA);
	gl::glEnable(gl::GLenum::GL_CULL_FACE);
	gl::glEnable(gl::GLenum::GL_PROGRAM_POINT_SIZE);

	bool loop = true;

	gl::GLuint skyVAO, skyVBO;

	gl::glGenVertexArrays(1, &skyVAO);
	gl::glGenBuffers(1, &skyVBO);
	gl::glBindBuffer(gl::GLenum::GL_ARRAY_BUFFER, skyVBO);
	gl::glBufferData(gl::GLenum::GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, gl::GLenum::GL_STATIC_DRAW);
	gl::glBindVertexArray(skyVAO);
	gl::glEnableVertexAttribArray(0);
	gl::glVertexAttribPointer(0, 3, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 3*sizeof(float), 0);

	Shader* skyboxShader = ResourceManager::loadShader("../src/Shaders/skybox.vs.glsl", "../src/Shaders/skybox.fs.glsl", "", "skybox");

	Shader* modelShaders = ResourceManager::loadShader("../src/Shaders/model.vs.glsl", "../src/Shaders/model.fs.glsl", "", "model");
	Model nanosuit("../models/nanosuit/nanosuit.obj");
	nanosuit.position(glm::vec3(0.0f, -1.75f, 0.0f));
	nanosuit.scale(0.2f);

	Shader* voxelShader = ResourceManager::loadShader("../src/Shaders/voxel.vs.glsl","../src/Shaders/voxel.fs.glsl",""/*"../src/Shaders/voxel.gs.glsl"*/,"voxel");
	int amount = 100;

	std::vector<glm::mat4> modelMatrices;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(i, i, i));
		modelMatrices.push_back(model);
	}
	std::vector<glm::vec3> colours;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::vec3 colour = glm::vec3(0.01*i, 0.01 * i, 0.01 * i);
		colours.push_back(colour);
	}
	gl::glGenBuffers(1, &voxelVBO);
	gl::glBindBuffer(gl::GLenum::GL_ARRAY_BUFFER, voxelVBO);
	gl::glBufferData(gl::GLenum::GL_ARRAY_BUFFER, (sizeof(gl::GLfloat) * voxelVertices.size()) + (amount * sizeof(glm::mat4)) + (amount * sizeof(glm::vec3)), nullptr, gl::GLenum::GL_STATIC_DRAW);
	gl::glBufferSubData(gl::GLenum::GL_ARRAY_BUFFER, 0, sizeof(gl::GLfloat)* voxelVertices.size(), &voxelVertices[0]);
	gl::glBufferSubData(gl::GLenum::GL_ARRAY_BUFFER, sizeof(gl::GLfloat) * voxelVertices.size(), amount * sizeof(glm::mat4), &modelMatrices[0]);
	gl::glBufferSubData(gl::GLenum::GL_ARRAY_BUFFER, sizeof(gl::GLfloat) * voxelVertices.size() + amount * sizeof(glm::mat4), amount * sizeof(glm::vec3), &colours[0]);

	gl::glGenVertexArrays(1, &voxelVAO);
	gl::glBindVertexArray(voxelVAO);
	gl::glVertexAttribPointer(0, 3, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 3 * sizeof(float), 0);
	gl::glEnableVertexAttribArray(0);

	GLsizei vec4Size = sizeof(glm::vec4);
	gl::glEnableVertexAttribArray(1);
	gl::glVertexAttribPointer(1, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 4*vec4Size, (void*)(sizeof(gl::GLfloat) * voxelVertices.size()));
	gl::glEnableVertexAttribArray(2);
	gl::glVertexAttribPointer(2, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 4 * vec4Size, (void*)(sizeof(gl::GLfloat) * voxelVertices.size() + vec4Size));
	gl::glEnableVertexAttribArray(3);
	gl::glVertexAttribPointer(3, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 4 * vec4Size, (void*)(sizeof(gl::GLfloat) * voxelVertices.size() + (2 * vec4Size)));
	gl::glEnableVertexAttribArray(4);
	gl::glVertexAttribPointer(4, 4, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 4 * vec4Size, (void*)(sizeof(gl::GLfloat) * voxelVertices.size() + (3 * vec4Size)));

	gl::glVertexAttribDivisor(1, 1);
	gl::glVertexAttribDivisor(2, 1);
	gl::glVertexAttribDivisor(3, 1);
	gl::glVertexAttribDivisor(4, 1);

	gl::glEnableVertexAttribArray(5);
	gl::glVertexAttribPointer(5, 3, gl::GLenum::GL_FLOAT, gl::GL_FALSE, sizeof(glm::vec3), (void*)((sizeof(gl::GLfloat) * voxelVertices.size()) + (amount * sizeof(glm::mat4)) + sizeof(glm::vec3)));
	gl::glVertexAttribDivisor(5, 1);

	gl::glGenBuffers(1, &voxelEBO);
	gl::glBindBuffer(gl::GLenum::GL_ELEMENT_ARRAY_BUFFER, voxelEBO);
	gl::glBufferData(gl::GLenum::GL_ELEMENT_ARRAY_BUFFER, voxelIndices.size()*sizeof(gl::GLuint), &voxelIndices[0], gl::GLenum::GL_STATIC_DRAW);
	/*gl::glVertexAttribPointer(1, 1, gl::GLenum::GL_INT, gl::GL_FALSE, sizeof(int), (void*)sizeof(voxelPoints));
	gl::glEnableVertexAttribArray(1);*/

	//gl::glPolygonMode(gl::GLenum::GL_FRONT_AND_BACK, gl::GLenum::GL_LINE);

	auto r = std::make_unique<Renderer>();

	TextureCube* skyboxTex = ResourceManager::loadCube({
		"../resources/skybox/right.jpg",
		"../resources/skybox/left.jpg",
		"../resources/skybox/top.jpg",
		"../resources/skybox/bottom.jpg",
		"../resources/skybox/front.jpg",
		"../resources/skybox/back.jpg"
	},"skybox");

	uint32_t dt = 0;
	while (loop) {
		auto start = std::chrono::high_resolution_clock::now();
		loop = processInput(windowEvent, dt);
		r->set();

		//r->render(modelShaders, &camera, &nanosuit);

		voxelShader->use();
		gl::glBindVertexArray(voxelVAO);
		voxelShader->setMat4("transform", camera.perspective()*camera.view());
		//gl::glDrawElements(gl::GLenum::GL_TRIANGLES, voxelIndices.size(), gl::GLenum::GL_UNSIGNED_INT,0);
		gl::glDrawElementsInstanced(gl::GLenum::GL_TRIANGLES, voxelIndices.size(), gl::GLenum::GL_UNSIGNED_INT, 0, amount);
		//gl::glDrawArrays(gl::GLenum::GL_TRIANGLES, 0, 36);

		gl::glBindVertexArray(0);
		gl::glDepthFunc(gl::GLenum::GL_LEQUAL);
		skyboxShader->use();
		skyboxShader->setMat4("projection", camera.perspective());
		skyboxShader->setMat4("view", glm::mat4(glm::mat3(camera.view())));
		gl::glBindVertexArray(skyVAO);
		skyboxTex->bind();
		gl::glDrawArrays(gl::GLenum::GL_TRIANGLES, 0, 36);
		gl::glBindVertexArray(0);
		gl::glDepthFunc(gl::GLenum::GL_LESS);

		r->unset();

		dt = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
		SDL_GL_SwapWindow(window);
	}


	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}