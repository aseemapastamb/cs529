#include "Button.h"

#include "GameObject.h"
#include "EventManager.h"
#include "GameStateManager.h"
#include <iostream>

extern EventManager* gpEventManager;
extern GameStateManager* gpGameStateManager;

Button::Button():
	Component("Button"),
	mPressed(false)
{
}

Button::~Button()
{
}

void Button::Update()
{
}

void Button::HandleEvent(Event* pEvent) {
	ButtonPressEvent* event = (ButtonPressEvent*)pEvent;

	if (event->pObject1->mLabel == mpOwner->mLabel) {
		if (mpOwner->mLabel == "PlayButton") {
			gpGameStateManager->SetNextLevel("level1.json");
			return;
		}
		if (mpOwner->mLabel == "RestartLevelButton") {
			gpGameStateManager->SetNextLevel(gpGameStateManager->mPreviousLevel);
			return;
		}
		if (mpOwner->mLabel == "NextLevelButton") {
			gpGameStateManager->SetNextLevel("level2.json");
			return;
		}
		if (mpOwner->mLabel == "InstructionsButton") {
			gpGameStateManager->SetNextLevel("instructions.json");
			return;
		}
		if (mpOwner->mLabel == "MainMenuButton") {
			gpGameStateManager->SetNextLevel("level0.json");
			return;
		}
		if (mpOwner->mLabel == "QuitButton") {
			std::cout << "Quit" << std::endl;
			gpGameStateManager->Quit();
		}
	}
}
