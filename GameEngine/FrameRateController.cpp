/*  Start Header -

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is
prohibited.

File Name: Frame_Rate_Controller.cpp
Purpose: Definition of frame rate controller class and member functions
Language: C++
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS529_aseemapastamb_milestone_1
Author: Aseem Apastamb, aseem.apastamb, 60000620
Creation date: 10/13/2021

- End Header
----------------------------------------------------------------------- */

#include "FrameRateController.h"
#include <stdio.h>

FrameRateController::FrameRateController(unsigned int maxFrameRate) {
	if (maxFrameRate == 0) {
		maxFrameRate = 120;
	}
	mMaxFrameRate = maxFrameRate;
	ticksPerFrame = 1000 / mMaxFrameRate;
	startTicks = 0;
	endTicks = 0;
	frameTime = 0;
	deltaTime = 0;
}
FrameRateController::~FrameRateController() {

}

void FrameRateController::frameStartTime() {
	startTicks = SDL_GetTicks();
}

void FrameRateController::frameEndTime() {
	endTicks = SDL_GetTicks();
	while (endTicks - startTicks < ticksPerFrame) {
		endTicks = SDL_GetTicks();
	}
	frameTime = endTicks - startTicks;
	deltaTime = static_cast<float>(frameTime) / 1000.0f;
}

unsigned int FrameRateController::getFrameTime() {
	return frameTime;
}

float FrameRateController::getDeltaTime() {
	return deltaTime;
}