#pragma once
#include "Scene.h"
#include "Shader.h"
#include "Camera.h"
class ModelLoadingScene : public Scene
{
public:

	ModelLoadingScene();

	void Update();

	Shader multipleLightsShader;
	glm::mat4 model;
	glm::mat4 projection;
	glm::mat4 view;

	Camera* cam = nullptr;
};

