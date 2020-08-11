#pragma once

#include "Shader.h"
#include <string>

class Skybox
{
public:
	Skybox(const char* vertexShader, const char* fragmentShader);
	~Skybox();

	void Render();

private:
	Shader *shader;
	unsigned int VAO, VBO;
};

