#version 330 core

// output color (RGBA)
out vec4 FragColor;

// input from vertex shader
// color
in vec3 color;
// texture coords
in vec2 texCoord;

// texture
uniform vec3 myCol;
uniform sampler2D tex;
uniform int mode;

void main()
{
	switch (mode) {
	case 0:
		// assign color from texture
		FragColor = texture(tex, texCoord);
		break;
	case 1:
		// assign color from object
		FragColor = vec4(myCol, 1.0f);
		break;
	case 2:
		// assign vertex color
		FragColor = vec4(color, 1.0f);
		break;
	default:
		// assign color from texture
		FragColor = texture(tex, texCoord);
		break;
	}
}