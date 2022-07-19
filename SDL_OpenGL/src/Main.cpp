#include <glad/glad.h>
#include "SDL.h"
#include "SDL_image.h"
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdlib.h>
#include <iostream>

#include <fstream>
#include <string>
#include <sstream>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Globals.h"
#include "InputManager.h"
#include "Camera.h"

int screenWidth = 1280;
int screenHeight = 720;

bool appState = true;

InputManager* input;

SDL_Window* window;

void flip_surface(SDL_Surface* surface)
{
	SDL_LockSurface(surface);

	int pitch = surface->pitch; // row size
	char* temp = new char[pitch]; // intermediate buffer
	char* pixels = (char*)surface->pixels;

	for (int i = 0; i < surface->h / 2; ++i) {
		// get pointers to the two rows to swap
		char* row1 = pixels + i * pitch;
		char* row2 = pixels + (surface->h - i - 1) * pitch;

		// swap rows
		memcpy(temp, row1, pitch);
		memcpy(row1, row2, pitch);
		memcpy(row2, temp, pitch);
	}

	delete[] temp;

	SDL_UnlockSurface(surface);
}

static unsigned int LoadTextureOpenGL(std::string path)
{
	SDL_Surface* image = IMG_Load(path.c_str());

	flip_surface(image);

	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	const char* pixelF = SDL_GetPixelFormatName(image->format->format);
	
	std::string pixelFormat = pixelF;

	GLuint flag;

	if (pixelFormat == "SDL_PIXELFORMAT_RGB24") flag = GL_RGB;
	else if (pixelFormat == "SDL_PIXELFORMAT_ABGR8888") flag = GL_RGBA;
	else
	{
		std::cout << "ERROR Loading " << path << ". Pixel Format not supported" << std::endl;
		return 0;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, flag, GL_UNSIGNED_BYTE, image->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(image);

	return texture;
}

void framebuffer_size_callback(SDL_Window* window, int width, int height);

void ProcessInput()
{
	if (input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		appState = false;
}

static int resizingEventWatcher(void* data, SDL_Event* event) {
	if (event->type == SDL_WINDOWEVENT &&
		event->window.event == SDL_WINDOWEVENT_RESIZED) {
		SDL_Window* win = SDL_GetWindowFromID(event->window.windowID);
		if (win == (SDL_Window*)data) {
			std::cout << "Window " << event->window.windowID << "resized to " << event->window.data1 << " " << event->window.data2 << std::endl;
			framebuffer_size_callback(win, event->window.data1, event->window.data2);
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	SDL_GLContext glContext;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* windowSurface = nullptr;
	
	Uint32 flags = SDL_WINDOW_SHOWN;
	flags |= SDL_WINDOW_RESIZABLE;
	flags |= SDL_WINDOW_OPENGL;

	window = SDL_CreateWindow("OpenGL Implementation by Adria Sellares", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
											screenWidth, screenHeight, flags);
	windowSurface = SDL_GetWindowSurface(window);

	glContext = SDL_GL_CreateContext(window);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	SDL_ShowCursor(0);
	SDL_CaptureMouse(SDL_FALSE);

	// OpenGl code --------------------------------------------
	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEPTH_TEST);

	input = InputManager::GetInstance();

	// Camera Set Up

	Camera cam;

	// MVP set up
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(cam.fov), 1280.0f / 720.0f, 0.1f, 100.0f);

	glm::mat4 view = glm::lookAt(cam.cameraPos, cam.cameraPos + cam.cameraFront, cam.cameraUp);

	// Set up shader
	Shader basicShader("shaders/basic.shader.vertex", "shaders/basic.shader.fragment");

	// Set vertex buffer attributes
	float vertices[] = {
	 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,  // top right
	 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,   1.0f, 0.0f,// bottom right
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,// bottom left
	-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 1.0f,	0.0f, 1.0f,// top left 
	};

	float vertices2[] = {
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

	glm::vec3 cubePositions[] = {
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

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// Vertex Buffer Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);*/

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	// -----------------------------------------------------------------------------
	SDL_AddEventWatch(resizingEventWatcher, window);

	// Image loading using stbi_image.h
	{
		/*int width, height, nrChannels;
		unsigned char* data = stbi_load("images/containerTexture.jpg", &width, &height, &nrChannels, 0);

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);*/
	}

	// Image Loading using SDL_Image
	unsigned int texture1 = LoadTextureOpenGL("images/containerTexture.jpg");
	unsigned int texture2 = LoadTextureOpenGL("images/awesomefaceTexture.png");

	basicShader.use(); // don't forget to activate the shader before setting uniforms!  
	basicShader.setInt("texture1", 0);
	basicShader.setInt("texture2", 1); 

	basicShader.SetMatFloat4v("model", glm::value_ptr(model));
	basicShader.SetMatFloat4v("view", glm::value_ptr(view));
	basicShader.SetMatFloat4v("projection", glm::value_ptr(projection));


	while (appState)
	{
		input->UpdateInput();
		ProcessInput();
		
		cam.UpdateCamera();
		SDL_WarpMouseInWindow(window, screenWidth / 2, screenHeight / 2);

		cam.lastMouseX = screenWidth / 2;
		cam.lastMouseY = screenHeight / 2;

		projection = glm::perspective(glm::radians(cam.fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		basicShader.SetMatFloat4v("projection", glm::value_ptr(projection));

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		basicShader.use();
		glBindVertexArray(VAO);

		view = cam.GetLookAt();
		basicShader.SetMatFloat4v("view", glm::value_ptr(view));

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			basicShader.SetMatFloat4v("model", glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		input->mouse_wheel_y = 0;

		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case(SDL_QUIT):
				appState = false;
				break;
			case(SDL_MOUSEWHEEL):
				input->mouse_wheel_y = event.wheel.y;
				break;
			}
		}

		SDL_GL_SwapWindow(window);
	}

	SDL_Quit();
	return 1;
}

void framebuffer_size_callback(SDL_Window* window, int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, width, height);
}