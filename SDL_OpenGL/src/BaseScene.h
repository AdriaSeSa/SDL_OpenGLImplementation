#pragma once
#include <glad/glad.h>
#include "Scene.h"

#include "InputManager.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Camera.h"
#include "Shader.h"

class BaseScene : public Scene
{
public:
	BaseScene();

	~BaseScene();

	void Update();

private:
	void VertexBufferArraySetUp();

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	unsigned int texture1;
	unsigned int texture2;

	InputManager* input;

	glm::mat4 model;
	glm::mat4 projection;
	glm::mat4 view;

	Camera* cam = nullptr;
	Shader basicShader;

};

