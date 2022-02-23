#include "Texture.h"

Texture::Texture():
	mpSurface(nullptr),
	mTexID(0) {

}

Texture::Texture(SDL_Surface* _pSurface):
	mpSurface(_pSurface) {
	// generate opengl texture object
	glGenTextures(1, &mTexID);

	// bind texture
	glBindTexture(GL_TEXTURE_2D, mTexID);

	// configure algorithm to make image smaller or bigger
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// configure how texture repeats
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// assigns image to opengl texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mpSurface->w, mpSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, mpSurface->pixels);
	// generate mipmaps
	glGenerateMipmap(GL_TEXTURE_2D);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {

}

void Texture::Bind(GLuint unit, GLuint programID) {
	// assign texture to texture unit
	glActiveTexture((GLenum)((int)GL_TEXTURE0 + unit));
	// bind texture
	glBindTexture(GL_TEXTURE_2D, mTexID);

	int uniID = glGetUniformLocation(programID, "tex");
	glUniform1i(uniID, unit);
}

void Texture::UnBind() {
	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}
