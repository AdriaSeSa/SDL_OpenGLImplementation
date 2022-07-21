#include "Camera.h"
#include "InputManager.h"
#include "SDL.h"

Camera* Camera::instance = nullptr;

Camera::Camera()
{
	input = InputManager::GetInstance();
}

Camera* Camera::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Camera();
	}
	return instance;
}

void Camera::FreeInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void Camera::UpdateCamera()
{
	UpdateCameraInput();

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(direction);
}

glm::mat4 Camera::GetLookAt()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::UpdateCameraInput()
{
	const float cameraSpeed = 0.05f; // adjust accordingly
	if (input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		cameraPos += cameraSpeed * cameraFront;
	if (input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		cameraPos -= cameraSpeed * cameraFront;
	if (input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	// Mouse looking 
	float xoffset = input->mouse_x - lastMouseX;
	float yoffset = lastMouseY - input->mouse_y; // reversed since y-coordinates range from bottom to top
	lastMouseX = input->mouse_x;
	lastMouseY = input->mouse_y;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	pitch += yoffset;
	yaw += xoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// Mouse Zoom

	fov -= (float)input->mouse_wheel_y;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 90.0f)
		fov = 90.0f;

	lastMouseX = 1280 / 2;
	lastMouseY = 720 / 2;
}
