/*  Start Header -

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is
prohibited.

File Name: Resource_Manager.h
Purpose: Declaration of resource manager class and member functions
Language: C++
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS529_aseemapastamb_milestone_1
Author: Aseem Apastamb, aseem.apastamb, 60000620
Creation date: 10/13/2021

- End Header
----------------------------------------------------------------------- */

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "stdio.h"
#include <string>
#include <unordered_map>
#include "Texture.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	SDL_Surface* loadSurface(const char * pFilePath);
	Texture* loadTexture(const char * pFilePath);
public:
	std::unordered_map<std::string, SDL_Surface*> mSurfaces;
	std::unordered_map<std::string, Texture*> mTextures;

private:
private:
};