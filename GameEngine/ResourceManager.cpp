/*  Start Header -

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is
prohibited.

File Name: Resource_Manager.cpp
Purpose: Declaration of resource manager class and member functions
Language: C++
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS529_aseemapastamb_milestone_1
Author: Aseem Apastamb, aseem.apastamb, 60000620
Creation date: 10/13/2021

- End Header
----------------------------------------------------------------------- */

#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	IMG_Init(IMG_INIT_PNG);
}

ResourceManager::~ResourceManager() {
	for (auto i = mSurfaces.begin(); i != mSurfaces.end(); ++i) {
		SDL_FreeSurface(i->second);
	}
	mSurfaces.clear();
	for (auto i = mTextures.begin(); i != mTextures.end(); ++i) {
		delete i->second;
	}
	mTextures.clear();
}

SDL_Surface* ResourceManager::loadSurface(const char * pFilePath) {
	if (mSurfaces.find(pFilePath) == mSurfaces.end()) {
		SDL_Surface* loadedSurface = IMG_Load(pFilePath);

		SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);

		SDL_Surface* convertedSurface = SDL_ConvertSurface(loadedSurface, format, 0);

		mSurfaces[pFilePath] = convertedSurface;

		SDL_FreeFormat(format);
		SDL_FreeSurface(loadedSurface);
	}
	return mSurfaces.at(pFilePath);
}

Texture* ResourceManager::loadTexture(const char* pFilePath) {
	if (mTextures.find(pFilePath) == mTextures.end()) {
		mTextures[pFilePath] = new Texture(mSurfaces.at(pFilePath));
	}
	return mTextures.at(pFilePath);
}
