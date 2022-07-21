#pragma once

#include <glad/glad.h>

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

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
