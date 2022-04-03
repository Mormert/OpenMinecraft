#pragma once

#include "Shader.h"
#include <string>
#include <glm/glm.hpp>

class Skybox
{
public:
	Skybox(const char* vertexShader, const char* fragmentShader);
	~Skybox();

	void Render(const glm::vec3 &cameraDirection, int screenWidth, int screenHeight);

    void SetBrightness(float b);
    void SetHumidity(float h);

private:
	Shader *shader;
	unsigned int VAO, VBO;

    float brightness = 1.f;
    float humidity = 0.f;
};

