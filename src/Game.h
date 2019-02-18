#pragma once

namespace GameEngine {
	class Game {
	public:
		static enum GameState {
			GAME_ACTIVE,
			GAME_MENU,
			GAME_WIN
		};
		gl::GLboolean Keys[1024];
		gl::GLuint width, height;
		
		Game(gl::GLuint width, gl::GLuint height);
		~Game();

		void Init();
		void ProcessInput(gl::GLfloat dt);
		void Update(gl::GLfloat dt);
		void Render();
	};
}