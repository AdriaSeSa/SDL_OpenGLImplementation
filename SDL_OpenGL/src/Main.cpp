#include <glad/glad.h>
#include "SDL.h"
#include "SDL_image.h"
#include <stdlib.h>
#include <iostream>

void framebuffer_size_callback(SDL_Window* window, int width, int height);

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
	bool appState = true;

	SDL_GLContext glContext;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* windowSurface = nullptr;
	
	Uint32 flags = SDL_WINDOW_SHOWN;
	flags |= SDL_WINDOW_RESIZABLE;
	flags |= SDL_WINDOW_OPENGL;

	SDL_Window* window = SDL_CreateWindow("OpenGL Implementation by Adria Sellares", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, flags);
	windowSurface = SDL_GetWindowSurface(window);

	glContext = SDL_GL_CreateContext(window);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// OpenGl code --------------------------------------------
	glViewport(0, 0, 1280, 720);

	SDL_AddEventWatch(resizingEventWatcher, window);

	while (appState)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case(SDL_QUIT):
				appState = false;
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
	glViewport(0, 0, width, height);
}