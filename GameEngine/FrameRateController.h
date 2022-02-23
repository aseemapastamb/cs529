/*  Start Header -

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is
prohibited.

File Name: Frame_Rate_Controller.h
Purpose: Declaration of frame rate controller class and member functions
Language: C++
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS529_aseemapastamb_milestone_1
Author: Aseem Apastamb, aseem.apastamb, 60000620
Creation date: 10/13/2021

- End Header
----------------------------------------------------------------------- */

#pragma once
#include <SDL.h>

class FrameRateController
{
public:
	FrameRateController(unsigned int maxFrameRate);
	~FrameRateController();
	void frameStartTime();
	void frameEndTime();
	unsigned int getFrameTime();
	float getDeltaTime();
public:

private:
private:
	unsigned int startTicks;
	unsigned int endTicks;
	unsigned int mMaxFrameRate;
	unsigned int ticksPerFrame;
	unsigned int frameTime;
	float deltaTime;
};