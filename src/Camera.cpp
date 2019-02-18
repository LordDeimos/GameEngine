#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

using namespace GameEngine;

Camera::Camera(glm::vec3 initPos){
	cameraPos = initPos;
	cameraFront = initPos + glm::vec3(0.0f, 0.0f, -1.0f);
	cameraDirection = glm::normalize(cameraPos - glm::vec3(0.0f, 0.0f, 0.0f));
	cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);
}


Camera::~Camera(){
}

glm::vec3 Camera::position() const {
	return cameraPos;
}

glm::vec3 Camera::front() const {
	return cameraFront;
}

glm::mat4 Camera::view() const {
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::perspective() const {
	return glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
}

float Camera::getFOV() const {
	return fov;
}

void Camera::move(Direction dir, uint32_t dt) {
	switch (dir) {
		case Direction::UP:
			cameraPos += cameraSpeed*dt * cameraFront;
			break;
		case Direction::DOWN:
			cameraPos -= cameraSpeed*dt * cameraFront;
			break;
		case Direction::LEFT:
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed*dt);
			break;
		case Direction::RIGHT:
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * (cameraSpeed*dt);
			break;
	}
}

void Camera::look(float x, float y) {

	float sensitivity = 0.05f;
	float xoffset = x*sensitivity;
	float yoffset = -1*y*sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void Camera::zoom(float amount) {
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= amount;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}