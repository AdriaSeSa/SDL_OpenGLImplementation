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

#include "BaseScene.h"
#include "LightingScene.h"
#include "MultipleLightsScene.h"

int screenWidth = 1280;
int screenHeight = 720;

bool appState = true;

InputManager* input;

SDL_Window* window;

float vertices[] = {
	 0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,  // top right
	 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,   1.0f, 0.0f,// bottom right
	-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,// bottom left
	-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 1.0f,	0.0f, 1.0f,// top left 
};

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

static void SetUp()
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
	}

	SDL_ShowCursor(0);
	SDL_CaptureMouse(SDL_FALSE);
}

int main(int argc, char* argv[])
{
	SetUp();

	// OpenGl code --------------------------------------------
	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEPTH_TEST);

	BaseScene baseScene;
	LightingScene lightingScene;
	MultipleLightsScene multipleLightsScene;

	Scene currentScene = multipleLightsScene;


	input = InputManager::GetInstance();

	// Camera Set Up
	Camera* cam = Camera::GetInstance();

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

	// Light Set up

	while (appState)
	{
		input->UpdateInput();

		cam->UpdateCamera();
		SDL_WarpMouseInWindow(window, screenWidth / 2, screenHeight / 2);

		multipleLightsScene.Update();

		ProcessInput();
		
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