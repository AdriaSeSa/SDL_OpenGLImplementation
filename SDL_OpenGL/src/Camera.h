#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class InputManager;

class Camera
{
public:

	static Camera* GetInstance();

	static void FreeInstance();

	void UpdateCamera();

	glm::mat4 GetLookAt();
	
private:
	Camera();
	void UpdateCameraInput();

public:

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	float fov = 45.0f;

	float lastMouseX;
	float lastMouseY;
private:

	static Camera* instance;

	glm::vec3 direction;

	float yaw = -90.0f;
	float pitch;

	float cameraSpeed = 0.05f;

	InputManager* input;

};

