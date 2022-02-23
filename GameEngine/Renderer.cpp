#include "Renderer.h"

#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include <glad/glad.h>
#include <SDL.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

extern SDL_Window* gpWindow;
extern GameObjectManager* gpGameObjectManager;
extern ResourceManager* gpResourceManager;
extern InputManager* gpInputManager;
extern int width, height;

Renderer::Renderer():
	mpMesh(nullptr),
	mpShaderProgram(nullptr),
	projMat(glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f)),
	modelMat(glm::mat4(1.0f)),
	mUniID(0),
	mode(0) {
}

Renderer::~Renderer() {
	delete mpMesh;
	delete mpShaderProgram;
}

void Renderer::Initialize() {
	mpMesh = new Mesh();
	// generate shader object
	mpShaderProgram = new Shader("default.vert", "default.frag");

	// create the mesh
	mpMesh->CreateMesh();

	// initialize colors
	InitializeColors();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Draw() {
	for (auto i : gpGameObjectManager->mGameObjects) {

		if (i->GetComponent("Transform")) {
			BuildTransforms(i);
		}

		// telling opengl which shader program to use
		mpShaderProgram->ActivateShaderProgram();

		mUniID = glGetUniformLocation(mpShaderProgram->ID, "modelMat");
		glUniformMatrix4fv(mUniID, 1, GL_FALSE, glm::value_ptr(modelMat));

		mUniID = glGetUniformLocation(mpShaderProgram->ID, "projMat");
		glUniformMatrix4fv(mUniID, 1, GL_FALSE, glm::value_ptr(projMat));

		if (i->GetComponent("Sprite")) {
			SendTextures(i);
		}

		//if (gpInputManager->isKeyTriggered(SDL_SCANCODE_M)) {
		//	++mode;
		//}
		if (gpInputManager->isKeyPressed(SDL_SCANCODE_M)) {
			mode = 1;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			mode = 0;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		mUniID = glGetUniformLocation(mpShaderProgram->ID, "mode");
		glUniform1i(mUniID, mode);

		//if (mode == 3) {
		//	mode = 0;
		//}

		// Bind VAO
		mpMesh->BindVAO();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		mpMesh->UnbindVAO();

		if (i->GetComponent("Sprite")) {
			//unbind texture
			UnbindTextures(i);
		}
	}
	// swap buffers
	SDL_GL_SwapWindow(gpWindow);
	Clear();
}

void Renderer::Clear() {
	// background color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// clean back buffer, assign new color
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::BuildTransforms(GameObject* pGameObject) {
	Transform* pTransform = (Transform*)pGameObject->GetComponent("Transform");

	modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, glm::vec3(pTransform->mPositionX, pTransform->mPositionY, 0.0f));
	modelMat = glm::rotate(modelMat, glm::radians(pTransform->mAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMat = glm::scale(modelMat, glm::vec3(pTransform->mScaleX, pTransform->mScaleY, 1.0f));
}

void Renderer::InitializeColors() {
	mColors["Red"] = glm::vec3(1.0f, 0.0f, 0.0f);
	mColors["Green"] = glm::vec3(0.0f, 1.0f, 0.0f);
	mColors["Blue"] = glm::vec3(0.0f, 0.0f, 1.0f);
	mColors["Yellow"] = glm::vec3(1.0f, 1.0f, 0.0f);
	mColors["Cyan"] = glm::vec3(0.0f, 1.0f, 1.0f);
	mColors["Violet"] = glm::vec3(1.0f, 0.0f, 1.0f);
}

void Renderer::SendTextures(GameObject* pGameObject) {
	Sprite* pSprite = (Sprite*)pGameObject->GetComponent("Sprite");

	pSprite->mpTexture->Bind(0, mpShaderProgram->ID);

	//pSprite->mpTexture->UnBind();

	mUniID = glGetUniformLocation(mpShaderProgram->ID, "myCol");
	glUniform3fv(mUniID, 1, &(mColors[pSprite->mColor][0]));
}

void Renderer::UnbindTextures(GameObject* pGameObject) {
	Sprite* pSprite = (Sprite*)pGameObject->GetComponent("Sprite");

	pSprite->mpTexture->UnBind();
}