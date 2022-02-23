#include "Shader.h"

// read text file and return a string
std::string readFile(const char* filename) {
	std::ifstream iFS;
	iFS.open(filename, std::ios_base::binary);
	std::string fileContent;
	iFS.seekg(0, std::ios_base::end);
	fileContent.resize(iFS.tellg());
	iFS.seekg(0, std::ios_base::beg);
	iFS.read(&fileContent[0], fileContent.size());
	iFS.close();
	return fileContent;
}

// build shader program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	// read shaders and store strings
	std::string vertCode = readFile(vertexFile);
	std::string fragCode = readFile(fragmentFile);

	// convert code to character arrays
	const char* vertexSourceCode = vertCode.c_str();
	const char* fragmentSourceCode = fragCode.c_str();

	// Creating Vertex shader and getting its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attaching vert shader src to vert shader obj
	glShaderSource(vertexShader, 1, &vertexSourceCode, NULL);
	// compiling
	glCompileShader(vertexShader);

	// Creating fragment shader and getting its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attaching frag shader src to frag shader obj
	glShaderSource(fragmentShader, 1, &fragmentSourceCode, NULL);
	// compiling
	glCompileShader(fragmentShader);

	// creating shader program
	ID = glCreateProgram();
	// attach vert and frag shaders to programs
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// link shaders
	glLinkProgram(ID);

	// deleting vert and frag shader objs
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(ID);
}

void Shader::ActivateShaderProgram() {
	glUseProgram(ID);
}

//void Shader::DeleteShaderProgram() {
//	glDeleteProgram(ID);
//}