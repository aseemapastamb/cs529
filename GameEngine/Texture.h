#pragma once

#include "SDL.h"
#include <string>
#include <glad/glad.h>

class Texture{
public:
	Texture();
	Texture(SDL_Surface* _pSurface);
	~Texture();

	void Bind(GLuint unit, GLuint programID);
	void UnBind();
public:
	SDL_Surface* mpSurface;
	GLuint mTexID;

private:
private:
};