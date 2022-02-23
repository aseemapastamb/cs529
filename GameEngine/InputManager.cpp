/*  Start Header -

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is
prohibited.

File Name: Input_Manager.cpp
Purpose: Definition of input manager class and member functions
Language: C++
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS529_aseemapastamb_milestone_1
Author: Aseem Apastamb, aseem.apastamb, 60000620
Creation date: 10/13/2021

- End Header
----------------------------------------------------------------------- */

#include "InputManager.h"
#include "memory.h"
#include "SDL_keyboard.h"
#include <SDL.h>

InputManager::InputManager():
	mMouseCurrentState(0),
	mMousePreviousState(0),
	mMouseX(0),
	mMouseY(0)
{
	memset(mCurrentState, 0, 512 * sizeof(Uint8));
	memset(mPreviousState, 0, 512 * sizeof(Uint8));
	//memset(mMouseCurrentState, 0, 3 * sizeof(Uint8));
	//memset(mMousePreviousState, 0, 3 * sizeof(Uint8));
}
InputManager::~InputManager() {

}
void InputManager::Update() {
	//Uint8 currentMouseStates[3] = { 0 };

	//SDL_Event e;
	//while (SDL_PollEvent(&e) != 0) {
	//	switch (e.type) {
	//	case SDL_MOUSEBUTTONUP:
	//		currentMouseStates[e.button.button - 1] = 0;
	//		break;
	//	case SDL_MOUSEBUTTONDOWN:
	//		currentMouseStates[e.button.button - 1] = 1;
	//		break;
	//	}
	//}
	//memcpy(mMousePreviousState, mMouseCurrentState, 3 * sizeof(Uint8));
	//memcpy(mMouseCurrentState, currentMouseStates, 3 * sizeof(Uint8));

	mMousePreviousState = mMouseCurrentState;
	mMouseCurrentState = SDL_GetMouseState(&mMouseX, &mMouseY);

	int numberOfItems = 0;
	const Uint8 * currentKeyStates = SDL_GetKeyboardState(&numberOfItems);
	if (numberOfItems > 512) {
		numberOfItems = 512;
	}
	memcpy(mPreviousState, mCurrentState, numberOfItems * sizeof(Uint8));
	memcpy(mCurrentState, currentKeyStates, numberOfItems * sizeof(Uint8));
}

// Keyboard
bool InputManager::isKeyPressed(unsigned int keyScanCode) {
	if (keyScanCode >= 512) {
		return false;
	}
	if (mCurrentState[keyScanCode]) {
		return true;
	}
	return false;
}

bool InputManager::isKeyReleased(unsigned int keyScanCode) {
	if (keyScanCode >= 512) {
		return false;
	}
	if (mPreviousState[keyScanCode] && !mCurrentState[keyScanCode]) {
		return true;
	}
	return false;
}

bool InputManager::isKeyTriggered(unsigned int keyScanCode) {
	if (keyScanCode >= 512) {
		return false;
	}
	if (!mPreviousState[keyScanCode] && mCurrentState[keyScanCode]) {
		return true;
	}
	return false;
}

// Mouse
bool InputManager::isButtonPressed(Uint32 buttonMask) {
	return mMouseCurrentState && buttonMask;
}

bool InputManager::isButtonReleased(Uint32 buttonMask) {
	return (mMousePreviousState && buttonMask) && (!(mMouseCurrentState && buttonMask));
}

bool InputManager::isButtonTriggered(Uint32 buttonMask) {
	return (!(mMousePreviousState && buttonMask)) && (mMouseCurrentState && buttonMask);
}