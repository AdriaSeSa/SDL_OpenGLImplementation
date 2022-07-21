#include "LightingScene.h"
#include "TextureLoad.h"

float vertices3[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

LightingScene::LightingScene()
{
	cam = Camera::GetInstance();

	VertexBufferArraySetUp();

	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	projection = glm::perspective(glm::radians(cam->fov), 1280.0f / 720.0f, 0.1f, 100.0f);

	view = glm::lookAt(cam->cameraPos, cam->cameraPos + cam->cameraFront, cam->cameraUp);

	basicShader.CreateShader("shaders/basic.shader.vertex", "shaders/basic.shader.fragment");

	basicShader.use(); // don't forget to activate the shader before setting uniforms!  
	basicShader.setInt("texture1", 0);
	basicShader.setInt("texture2", 1);

	basicShader.SetMatFloat4v("model", glm::value_ptr(model));
	basicShader.SetMatFloat4v("view", glm::value_ptr(view));
	basicShader.SetMatFloat4v("projection", glm::value_ptr(projection));

	texture1 = LoadTextureOpenGL("images/containerTexture.jpg");
	texture2 = LoadTextureOpenGL("images/awesomefaceTexture.png");

	lightingShader.CreateShader("shaders/light.shader.vertex", "shaders/light.shader.fragment");
	lightingShader.use();
	lightingShader.SetFloat3("objectColor", 1.0f, 0.5f, 0.31f);
	lightingShader.SetFloat3("lightColor", 1.0f, 1.0f, 1.0f);

	lightingShader.SetMatFloat4v("model", glm::value_ptr(model));
	lightingShader.SetMatFloat4v("view", glm::value_ptr(view));
	lightingShader.SetMatFloat4v("projection", glm::value_ptr(projection));

	lightCubeShader.CreateShader("shaders/light.shader.vertex", "shaders/lightCube.shader.fragment");
	lightCubeShader.use();
	lightCubeShader.SetMatFloat4v("model", glm::value_ptr(model));
	lightCubeShader.SetMatFloat4v("view", glm::value_ptr(view));
	lightCubeShader.SetMatFloat4v("projection", glm::value_ptr(projection));

}

LightingScene::~LightingScene()
{
}

void LightingScene::Update()
{
	projection = glm::perspective(glm::radians(cam->fov), (float)1280 / (float)720, 0.1f, 100.0f);
	view = cam->GetLookAt();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	lightingShader.use();
	glBindVertexArray(VAO);

	lightingShader.SetMatFloat4v("projection", glm::value_ptr(projection));
	lightingShader.SetMatFloat4v("view", glm::value_ptr(view));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	lightCubeShader.use();
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);

	//-------------------------------------------------
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glGenBuffers(1, &lightVBO);

	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	// set the vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);
}
