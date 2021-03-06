#include "LightingScene.h"
#include "TextureLoad.h"

float vertices3[] = {
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

glm::vec3 cubePositions2[] = {
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

LightingScene::LightingScene()
{
	cam = Camera::GetInstance();

	VertexBufferArraySetUp();

	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	projection = glm::perspective(glm::radians(cam->fov), 1280.0f / 720.0f, 0.1f, 100.0f);

	view = glm::lookAt(cam->cameraPos, cam->cameraPos + cam->cameraFront, cam->cameraUp);

	diffuseMap = LoadTextureOpenGL("images/containerTexture2.png");
	specularMap = LoadTextureOpenGL("images/container2_specularTexture.png");

	lightingShader.CreateShader("shaders/light.shader.vertex", "shaders/light.shader.fragment");
	lightingShader.use();

	lightingShader.SetMatFloat4v("model", glm::value_ptr(model));
	lightingShader.SetMatFloat4v("view", glm::value_ptr(view));
	lightingShader.SetMatFloat4v("projection", glm::value_ptr(projection));

	lightingShader.SetFloat3("material.ambient", 1.0f, 0.5f, 0.31f);	// Material ambient component
	lightingShader.setInt("material.diffuse", 0);						// Material diffuse component set by map (0  is texture slot)
	lightingShader.setInt("material.specular", 1);						// Material specular component set by map (1  is texture slot)
	lightingShader.setFloat("material.shininess", 32.0f);				// Material shininess component

	lightingShader.SetFloat3("light.direction", -0.2f, -1.0f, -0.3f);
	lightingShader.SetFloat3("light.ambient", 0.2f, 0.2f, 0.2f);		// Light ambient component
	lightingShader.SetFloat3("light.diffuse", 0.5f, 0.5f, 0.5f);		// Light diffuse component
	lightingShader.SetFloat3("light.specular", 1.0f, 1.0f, 1.0f);		// Light specular component

	lightingShader.setFloat("light.constant", 1.0f);
	lightingShader.setFloat("light.linear", 0.09f);
	lightingShader.setFloat("light.quadratic", 0.032f);

	lightCubeShader.CreateShader("shaders/light.shader.vertex", "shaders/lightCube.shader.fragment");
	lightCubeShader.use();
	lightCubeShader.SetMatFloat4v("model", glm::value_ptr(model));
	lightCubeShader.SetMatFloat4v("view", glm::value_ptr(view));
	lightCubeShader.SetMatFloat4v("projection", glm::value_ptr(projection));
	lightCubeShader.SetFloat3("lightColor", 1.0f, 1.0f, 1.0f);

	spotLightShader.CreateShader("shaders/light.shader.vertex", "shaders/spotLight.shader.fragment");
	spotLightShader.use();

	spotLightShader.SetFloat3("light.position", cam->cameraPos.x, cam->cameraPos.y, cam->cameraPos.z);
	spotLightShader.SetFloat3("light.direction", cam->cameraFront.x, cam->cameraFront.y, cam->cameraFront.z);
	spotLightShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
	spotLightShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));

	spotLightShader.SetFloat3("light.direction", -0.2f, -1.0f, -0.3f);
	spotLightShader.SetFloat3("light.ambient", 0.1f, 0.1f, 0.1f);		// Light ambient component
	spotLightShader.SetFloat3("light.diffuse", 0.5f, 0.5f, 0.5f);		// Light diffuse component
	spotLightShader.SetFloat3("light.specular", 1.0f, 1.0f, 1.0f);		// Light specular component

	spotLightShader.setInt("material.diffuse", 0);						// Material diffuse component set by map (0  is texture slot)
	spotLightShader.setInt("material.specular", 1);						// Material specular component set by map (1  is texture slot)
	spotLightShader.setFloat("material.shininess", 32.0f);				// Material shininess component

	spotLightShader.SetMatFloat4v("model", glm::value_ptr(model));
	spotLightShader.SetMatFloat4v("view", glm::value_ptr(view));
	spotLightShader.SetMatFloat4v("projection", glm::value_ptr(projection));

}

LightingScene::~LightingScene()
{
}

void LightingScene::Update()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	projection = glm::perspective(glm::radians(cam->fov), (float)1280 / (float)720, 0.1f, 100.0f);
	view = cam->GetLookAt();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	spotLightShader.use();
	glBindVertexArray(VAO);

	spotLightShader.SetFloat3("light.position", cam->cameraPos.x, cam->cameraPos.y, cam->cameraPos.z);
	spotLightShader.SetFloat3("light.direction", cam->cameraFront.x, cam->cameraFront.y, cam->cameraFront.z);

	spotLightShader.SetMatFloat4v("projection", glm::value_ptr(projection));
	spotLightShader.SetMatFloat4v("view", glm::value_ptr(view));

	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions2[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		spotLightShader.SetMatFloat4v("model", glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glDrawArrays(GL_TRIANGLES, 0, 36);

	/*glm::vec3 lightColor;
	lightColor.x = sin((SDL_GetTicks()/1000.0f) * 2.0f);
	lightColor.y = sin((SDL_GetTicks() / 1000.0f) * 0.7f);
	lightColor.z = sin((SDL_GetTicks() / 1000.0f) * 1.3f);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

	lightingShader.SetFloat3("light.ambient", lightColor.x, lightColor.y, lightColor.z);
	lightingShader.SetFloat3("light.diffuse", diffuseColor.x, diffuseColor.y, diffuseColor.z);*/


	lightCubeShader.use();
	//lightCubeShader.SetFloat3("lightColor", lightColor.x, lightColor.y, lightColor.z);

	glBindVertexArray(lightVAO);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	glm::mat4 model2 = glm::mat4(1.0f);
	model2 = glm::translate(model2, lightPos);
	model2 = glm::scale(model2, glm::vec3(0.2f));

	lightCubeShader.SetMatFloat4v("model", glm::value_ptr(model2));
	lightCubeShader.SetMatFloat4v("projection", glm::value_ptr(projection));
	lightCubeShader.SetMatFloat4v("view", glm::value_ptr(view));

	// draw the light cube object
;
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void LightingScene::VertexBufferArraySetUp()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	// set the vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
