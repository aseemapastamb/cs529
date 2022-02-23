#pragma once

#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize();
	void Draw();
	void Clear();
	void BuildTransforms(GameObject* pGameObject);
	void InitializeColors();
	void SendTextures(GameObject* pGameObject);
	void UnbindTextures(GameObject* pGameObject);
private:
	Mesh* mpMesh;
	Shader* mpShaderProgram;
	GLuint mUniID;
	glm::mat4 projMat, modelMat;
	std::unordered_map <std::string, glm::vec3> mColors;
	int mode;
};