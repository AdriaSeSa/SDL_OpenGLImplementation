#pragma once

#include <glad/glad.h>
#include "Scene.h"

#include "InputManager.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Camera.h"
#include "Shader.h"
class LightingScene : public Scene
{
public:
	LightingScene();

	~LightingScene();

	void Update();

private:
	void VertexBufferArraySetUp();

private:
	unsigned int VAO;
	unsigned int lightVAO;
	unsigned int VBO;
	unsigned int lightVBO;

	unsigned int diffuseMap;
	unsigned int specularMap;

	InputManager* input;

	glm::mat4 model;
	glm::mat4 projection;
	glm::mat4 view;

	Camera* cam = nullptr;
	Shader lightingShader;
	Shader basicShader;
	Shader lightCubeShader;
	Shader spotLightShader;
};

