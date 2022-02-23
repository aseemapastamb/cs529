#include "Mesh.h"

Mesh::Mesh():
	VAOID(0),
	VBOID(0),
	EBOID(0) {

}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAOID);
	glDeleteBuffers(1, &VBOID);
	glDeleteBuffers(1, &EBOID);
}

void Mesh::BindVAO() {
	glBindVertexArray(VAOID);
}

void Mesh::UnbindVAO() {
	glBindVertexArray(0);
}

void Mesh::CreateMesh() {
	// generate VAO with 1 obj and bind it
	glGenVertexArrays(1, &VAOID);
	BindVAO();

	// generate VBO with 1 obj and link to vertices
	glGenBuffers(1, &VBOID);
	// bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	// vertices into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// generate EBO with 1 obj and link to indices
	glGenBuffers(1, &EBOID);
	// binding EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);
	// indices into EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position
	// link VBO to VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	// configure vertex attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// enable vertex attrib
	glEnableVertexAttribArray(0);
	// unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// color
	// link VBO to VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	// configure vertex attrib
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// enable vertex attrib
	glEnableVertexAttribArray(1);
	// unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// texture coords
	// link VBO to VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	// configure vertex attrib
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// enable vertex attrib
	glEnableVertexAttribArray(2);
	// unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unbind VAO
	UnbindVAO();
	// unbind EBO
	// unbind EBO after unbinding VAO -> EBO is linked in VAO
	// does not apply to VBO as VBO is already linked to VAO during glVertexAtrribPointer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}