
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
// positions all containers
std::vector<glm::vec3> cubePositions = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
// positions of the point lights
std::vector<glm::vec3> pointLightPositions = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
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

const char* cubeVert = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 transform;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    TexCoords = aTexCoords;
    
    gl_Position = transform * vec4(FragPos, 1.0);
}
)glsl";

const char* cubeFrag = R"glsl(
#version 330 core
out vec4 FragColour;
void main(){
	FragColour = vec4(0.1,0.5,0.25,1.0);
}
)glsl";

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

gl::GLuint loadCubeMap(std::vector<std::string> faces) {
	gl::GLuint textureID;
	gl::glGenTextures(1, &textureID);
	gl::glBindTexture(gl::GLenum::GL_TEXTURE_CUBE_MAP, textureID);

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		auto data = std::make_unique<Image>(faces[i]);
		if (data){
			glTexImage2D(gl::GLenum::GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, gl::GLenum::GL_RGBA, data->width, data->height, 0, gl::GLenum::GL_RGBA, gl::GLenum::GL_UNSIGNED_BYTE, data->image);
		}
		else{
			std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
		}
	}
	glTexParameteri(gl::GLenum::GL_TEXTURE_CUBE_MAP, gl::GLenum::GL_TEXTURE_MIN_FILTER, gl::GLenum::GL_LINEAR);
	glTexParameteri(gl::GLenum::GL_TEXTURE_CUBE_MAP, gl::GLenum::GL_TEXTURE_MAG_FILTER, gl::GLenum::GL_LINEAR);
	glTexParameteri(gl::GLenum::GL_TEXTURE_CUBE_MAP, gl::GLenum::GL_TEXTURE_WRAP_S, gl::GLenum::GL_CLAMP_TO_EDGE);
	glTexParameteri(gl::GLenum::GL_TEXTURE_CUBE_MAP, gl::GLenum::GL_TEXTURE_WRAP_T, gl::GLenum::GL_CLAMP_TO_EDGE);
	glTexParameteri(gl::GLenum::GL_TEXTURE_CUBE_MAP, gl::GLenum::GL_TEXTURE_WRAP_R, gl::GLenum::GL_CLAMP_TO_EDGE);

	return textureID;
}

GLuint compileShader(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr)
{
	GLuint sVertex, sFragment, gShader, ID;
	// Vertex Shader
	sVertex = gl::glCreateShader(gl::GLenum::GL_VERTEX_SHADER);
	gl::glShaderSource(sVertex, 1, &vertexSource, NULL);
	gl::glCompileShader(sVertex);
	//checkErrors(sVertex, "Vertex");
	// Fragment Shader
	sFragment = gl::glCreateShader(gl::GLenum::GL_FRAGMENT_SHADER);
	gl::glShaderSource(sFragment, 1, &fragmentSource, NULL);
	gl::glCompileShader(sFragment);
	//checkErrors(sFragment, "Fragment");
	// If geometry shader source code is given, also compile geometry shader
	if (geometrySource != nullptr)
	{
		gShader = gl::glCreateShader(gl::GLenum::GL_GEOMETRY_SHADER);
		gl::glShaderSource(gShader, 1, &geometrySource, NULL);
		gl::glCompileShader(gShader);
		//checkErrors(gShader, "Geometry");
	}
	// Shader Program
	ID = gl::glCreateProgram();
	gl::glAttachShader(ID, sVertex);
	gl::glAttachShader(ID, sFragment);
	if (geometrySource != nullptr)
		gl::glAttachShader(ID, gShader);
	gl::glLinkProgram(ID);
	//checkErrors(ID, "Program");
	// Delete the shaders as they're linked into our program now and no longer necessery
	gl::glDeleteShader(sVertex);
	gl::glDeleteShader(sFragment);
	if (geometrySource != nullptr)
		gl::glDeleteShader(gShader);
	return ID;
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
	//gl::glEnable(gl::GLenum::GL_CULL_FACE);

	bool loop = true;
	GLuint frameBuffer, colourBuffer, renderBuffer, frameVAO, frameVBO, shaderID;
	gl::glGenVertexArrays(1, &frameVAO);
	gl::glBindVertexArray(frameVAO);
	gl::glGenBuffers(1, &frameVBO);
	gl::glBindBuffer(gl::GLenum::GL_ARRAY_BUFFER, frameVBO);
	gl::glBufferData(gl::GLenum::GL_ARRAY_BUFFER, sizeof(vertices), vertices, gl::GLenum::GL_STATIC_DRAW);
	gl::glVertexAttribPointer(0, 3, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 8 * sizeof(float), (void*)0);
	gl::glEnableVertexAttribArray(0);
	gl::glVertexAttribPointer(1, 3, gl::GLenum::GL_FLOAT, gl::GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	gl::glEnableVertexAttribArray(1);

	shaderID = compileShader(cubeVert, cubeFrag);


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

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	auto r = std::make_unique<Renderer>();

	gl::GLuint skyboxTex =  loadCubeMap({
		"../resources/skybox/right.jpg",
		"../resources/skybox/left.jpg",
		"../resources/skybox/top.jpg",
		"../resources/skybox/bottom.jpg",
		"../resources/skybox/front.jpg",
		"../resources/skybox/back.jpg"
	});

	uint32_t dt = 0;
	while (loop) {
		auto start = std::chrono::high_resolution_clock::now();
		loop = processInput(windowEvent, dt);
		r->set();

		/*modelShaders->use();
		gl::glActiveTexture(gl::GLenum::GL_TEXTURE5);
		modelShaders->setFloat("skybox",skyboxTex);
		gl::glBindTexture(gl::GLenum::GL_TEXTURE_CUBE_MAP, skyboxTex);*/
		//r->render(modelShaders, &camera, &nanosuit);

		gl::glUseProgram(shaderID);
		glm::mat4 view = glm::mat4(1.0f);// camera.view();
		glm::mat4 projection = glm::mat4(1.0f);// camera.perspective();
		glm::mat4 transform = projection * view;
		gl::glUniformMatrix4fv(gl::glGetUniformLocation(shaderID, "transform"), 1, gl::GL_FALSE, glm::value_ptr(transform));
		glm::mat4 model = glm::mat4(1.0f);
		glm::translate(model, glm::vec3(-1.0f, -0.5f, -1.5f));
		glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		gl::glUniformMatrix4fv(gl::glGetUniformLocation(shaderID, "model"), 1, gl::GL_FALSE, glm::value_ptr(model));
		gl::glBindVertexArray(frameVAO);
		gl::glDrawArrays(gl::GLenum::GL_TRIANGLES, 0, 36);

		gl::glDepthFunc(gl::GLenum::GL_LEQUAL);
		skyboxShader->use();
		skyboxShader->setMat4("projection", camera.perspective());
		skyboxShader->setMat4("view", glm::mat4(glm::mat3(camera.view())));
		gl::glBindVertexArray(skyVAO);
		gl::glBindTexture(gl::GLenum::GL_TEXTURE_CUBE_MAP, skyboxTex);
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