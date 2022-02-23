#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void CreateMesh();
	void BindVAO();
	void UnbindVAO();
	//void DeleteMesh();
public:

private:
	GLfloat vertices[32] =
	{	// vertex coords			// colors					// tex coords
		-0.5f, -0.5f, 0.0f,			1.0f, 1.0f, 1.0f,			0.0f, 0.0f,		// lower left
		0.5f, -0.5f, 0.0f,			1.0f, 1.0f, 1.0f,			1.0f, 0.0f,		// lower right
		0.5f, 0.5f, 0.0f,			0.3f, 0.3f, 0.3f,			1.0f, 1.0f,		// upper right
		-0.5f, 0.5f, 0.0f,			0.3f, 0.3f, 0.3f,			0.0f, 1.0f		// upper left
	};
	// indices for vertex order
	GLuint indices[6] =
	{
		0, 1, 2,	// lower tri
		2, 3, 0		// upper tri
	};

	GLuint VAOID, VBOID, EBOID;
};

#endif