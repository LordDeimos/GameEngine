#pragma once
namespace GameEngine {
	class Camera
	{
	public:
		static enum Direction
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
		Camera(glm::vec3 initPos);
		~Camera();
		glm::mat4 view() const;
		glm::mat4 perspective() const;
		glm::vec3 position() const;
		glm::vec3 front() const;
		float getFOV() const;
		void move(Direction dir, uint32_t dt = 0);
		void look(float x, float y);
		void zoom(float amount);
	private:
		glm::vec3 cameraPos, cameraFront, cameraDirection, cameraRight, cameraUp;
		float cameraSpeed = 0.01f;
		float pitch = 0, yaw = 0;
		float fov = 45.0f;
	};
}

