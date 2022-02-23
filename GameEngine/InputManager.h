/*  Start Header -

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is
prohibited.

File Name: Input_Manager.h
Purpose: Declaration of input manager class and member functions
Language: C++
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS529_aseemapastamb_milestone_1
Author: Aseem Apastamb, aseem.apastamb, 60000620
Creation date: 10/13/2021

- End Header
----------------------------------------------------------------------- */

#pragma once
#include "SDL_stdinc.h"
class InputManager
{
public:
	InputManager();
	~InputManager();
	void Update();
	bool isKeyPressed(unsigned int keyScanCode);
	bool isKeyReleased(unsigned int keyScanCode);
	bool isKeyTriggered(unsigned int keyScanCode);
	bool isButtonPressed(Uint32 buttonMask);
	bool isButtonReleased(Uint32 buttonMask);
	bool isButtonTriggered(Uint32 buttonMask);
public:
	int mMouseX, mMouseY;

private:
private:
	Uint8 mCurrentState[512];
	Uint8 mPreviousState[512];
	Uint32 mMouseCurrentState;
	Uint32 mMousePreviousState;
	//Uint8 mMouseCurrentState[3];
	//Uint8 mMousePreviousState[3];
};