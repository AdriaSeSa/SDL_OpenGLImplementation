#include "ModelLoadingScene.h"
#include "Model.h"

Model* modelBackpack = nullptr;

glm::vec3 pointLightPositions2[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

ModelLoadingScene::ModelLoadingScene()
{
	 cam = Camera::GetInstance();

	 model = glm::mat4(1.0f);
	 model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	 projection = glm::perspective(glm::radians(cam->fov), 1280.0f / 720.0f, 0.1f, 100.0f);

	 view = glm::lookAt(cam->cameraPos, cam->cameraPos + cam->cameraFront, cam->cameraUp);
	 modelBackpack = new Model("backpack/backpack.obj");

	 // Initialize Multiple Light Shader
	 multipleLightsShader.CreateShader("shaders/light.shader.vertex", "shaders/multipleLights.shader.fragment");
	 multipleLightsShader.use();

	 // Init MVP
	 multipleLightsShader.SetMatFloat4v("model", glm::value_ptr(model));
	 multipleLightsShader.SetMatFloat4v("view", glm::value_ptr(view));
	 multipleLightsShader.SetMatFloat4v("projection", glm::value_ptr(projection));

	 // Init view Position (camera position)
	 multipleLightsShader.SetFloat3("viewPos", cam->cameraPos.x, cam->cameraPos.y, cam->cameraPos.z);

	 // Init Directional Light
	 multipleLightsShader.SetFloat3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	 multipleLightsShader.SetFloat3("dirLight.ambient", 0.0f, 0.0f, 0.0f);		// Light ambient component
	 multipleLightsShader.SetFloat3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);		// Light diffuse component
	 multipleLightsShader.SetFloat3("dirLight.specular", 1.0f, 1.0f, 1.0f);		// Light specular component

	 // Init Point Lights
	 for (int i = 0; i < 4; i++)
	 {
		 std::string uniformName = "pointLights[" + std::to_string(i) + "]";

		 // Set position
		 multipleLightsShader.SetFloat3(uniformName + ".position", pointLightPositions2[i].x, pointLightPositions2[i].y, pointLightPositions2[i].z);

		 // Set Constant, Linear and Quadratic
		 multipleLightsShader.setFloat(uniformName + ".constant", 1.0f);
		 multipleLightsShader.setFloat(uniformName + ".linear", 0.09f);
		 multipleLightsShader.setFloat(uniformName + ".quadratic", 0.032f);

		 // Set Ambient, difuse, specular
		 multipleLightsShader.SetFloat3(uniformName + ".ambient", 0.0f, 0.0f, 0.0f);		// Light ambient component
		 multipleLightsShader.SetFloat3(uniformName + ".diffuse", 0.5f, 0.5f, 0.5f);		// Light diffuse component
		 multipleLightsShader.SetFloat3(uniformName + ".specular", 1.0f, 1.0f, 1.0f);		// Light specular component

	 }

	 // Init Spot light
	 multipleLightsShader.SetFloat3("spotLight.ambient", 0.0f, 0.0f, 0.0f);		// Light ambient component
	 multipleLightsShader.SetFloat3("spotLight.diffuse", 0.5f, 0.5f, 0.5f);		// Light diffuse component
	 multipleLightsShader.SetFloat3("spotLight.specular", 1.0f, 1.0f, 1.0f);		// Light specular component

	 multipleLightsShader.SetFloat3("spotLight.position", cam->cameraPos.x, cam->cameraPos.y, cam->cameraPos.z);
	 multipleLightsShader.SetFloat3("spotLight.direction", cam->cameraFront.x, cam->cameraFront.y, cam->cameraFront.z);
	 multipleLightsShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	 multipleLightsShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));

	 //Init Material
	 multipleLightsShader.setInt("material.diffuse", 0);						// Material diffuse component set by map (0  is texture slot)
	 multipleLightsShader.setInt("material.specular", 1);						// Material specular component set by map (1  is texture slot)
	 multipleLightsShader.setFloat("material.shininess", 32.0f);				// Material shininess component
}

void ModelLoadingScene::Update()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// calculate Projection and View matrix for this frame
	projection = glm::perspective(glm::radians(cam->fov), (float)1280 / (float)720, 0.1f, 100.0f);  // Fov could change
	view = cam->GetLookAt(); // Position and viewDirection could change
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

	multipleLightsShader.use();

	multipleLightsShader.SetMatFloat4v("projection", glm::value_ptr(projection));
	multipleLightsShader.SetMatFloat4v("view", glm::value_ptr(view));
	multipleLightsShader.SetMatFloat4v("model", glm::value_ptr(model));


	modelBackpack->Draw(multipleLightsShader);
}
