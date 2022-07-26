#include "MultipleLightsScene.h"
#include "TextureLoad.h"

float vertices4[] = {
	// positions          // normals           // texture coords
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions4[] = {
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

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

MultipleLightsScene::MultipleLightsScene()
{
	cam = Camera::GetInstance();

	VertexBufferArraySetUp();

	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	projection = glm::perspective(glm::radians(cam->fov), 1280.0f / 720.0f, 0.1f, 100.0f);

	view = glm::lookAt(cam->cameraPos, cam->cameraPos + cam->cameraFront, cam->cameraUp);

	diffuseMap = LoadTextureOpenGL("images/containerTexture2.png");
	specularMap = LoadTextureOpenGL("images/container2_specularTexture.png");

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
		multipleLightsShader.SetFloat3(uniformName + ".position", pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);		

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

	lightCubeShader.CreateShader("shaders/light.shader.vertex", "shaders/lightCube.shader.fragment");
	lightCubeShader.use();
	lightCubeShader.SetMatFloat4v("model", glm::value_ptr(model));
	lightCubeShader.SetMatFloat4v("view", glm::value_ptr(view));
	lightCubeShader.SetMatFloat4v("projection", glm::value_ptr(projection));
	lightCubeShader.SetFloat3("lightColor", 1.0f, 1.0f, 1.0f);
}

MultipleLightsScene::~MultipleLightsScene()
{
}

void MultipleLightsScene::Update()
{
	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	// calculate Projection and View matrix for this frame
	projection = glm::perspective(glm::radians(cam->fov), (float)1280 / (float)720, 0.1f, 100.0f);  // Fov could change
	view = cam->GetLookAt(); // Position and viewDirection could change

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind shader and Vertex Array
	multipleLightsShader.use();
	glBindVertexArray(VAO);

	// update Flashlight (spotlight) position and view Direction based on the ones inside our camera.
	multipleLightsShader.SetFloat3("spotLight.position", cam->cameraPos.x, cam->cameraPos.y, cam->cameraPos.z);
	multipleLightsShader.SetFloat3("spotLight.direction", cam->cameraFront.x, cam->cameraFront.y, cam->cameraFront.z);
	multipleLightsShader.SetFloat3("viewPos", cam->cameraPos.x, cam->cameraPos.y, cam->cameraPos.z);

	// Update shader's projection and view matrix
	multipleLightsShader.SetMatFloat4v("projection", glm::value_ptr(projection));
	multipleLightsShader.SetMatFloat4v("view", glm::value_ptr(view));

	// Draw multiple cubes
	for (unsigned int i = 0; i < 10; i++)
	{
		// Calculate model matrix
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions4[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

		// Update shader's model matrix
		multipleLightsShader.SetMatFloat4v("model", glm::value_ptr(model));

		// Draw cubes
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// Use light Cube shader and bind its vertex Array
	lightCubeShader.use();
	glBindVertexArray(lightVAO);

	lightCubeShader.SetMatFloat4v("projection", glm::value_ptr(projection));
	lightCubeShader.SetMatFloat4v("view", glm::value_ptr(view));

	for (int i = 0; i < 4; i++)
	{
		glm::vec3 lightPos = pointLightPositions[i];
		glm::mat4 model2 = glm::mat4(1.0f);
		model2 = glm::translate(model2, lightPos);
		model2 = glm::scale(model2, glm::vec3(0.2f));

		// Update Model.
		lightCubeShader.SetMatFloat4v("model", glm::value_ptr(model2));
		// draw the light cube object
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void MultipleLightsScene::VertexBufferArraySetUp()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
	glEnableVertexAttribArray(2);


	//-------------------------------------------------
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glGenBuffers(1, &lightVBO);

	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);

	// set the vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
