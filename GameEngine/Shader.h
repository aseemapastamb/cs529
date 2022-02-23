#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>

std::string readFile(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	void ActivateShaderProgram();
	//void DeleteShaderProgram();
};

#endif