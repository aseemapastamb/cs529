#version 330 core

// position
layout (location = 0) in vec3 aPos;
// color
layout (location = 1) in vec3 aColor;
// texture coords
layout (location = 2) in vec2 aTexCoord;

// output to fragment shader
out vec3 color;
out vec2 texCoord;

// Uniform variables
uniform mat4 modelMat;
uniform mat4 projMat;

void main()
{
	// output position of all vertices
	gl_Position = projMat * modelMat * vec4(aPos, 1.0f);
	
	// assign vertex color
	color = aColor;

	// assign texture coords
	texCoord = aTexCoord;
}