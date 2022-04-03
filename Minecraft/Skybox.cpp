#include "Skybox.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

Skybox::Skybox(const char* vertexShader, const char* fragmentShader)
{
	shader = new Shader(vertexShader, fragmentShader);


	constexpr float vertices[] = { // Screen quad
		-1.0f,	-1.0f,
		1.0f,	-1.0f,
		1.0f,	1.0f,
		1.0f,	1.0f,
		-1.0f,	1.0f,
		-1.0f,	-1.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

Skybox::~Skybox()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	delete shader;
}

void Skybox::Render(const glm::vec3 &cameraDirection, int screenWidth, int screenHeight)
{
	glDisable(GL_DEPTH_TEST);

	shader->Use();
	shader->SetVec3("camdir", cameraDirection);
	shader->SetVec2("resolution", glm::vec2{ static_cast<float>(screenWidth), static_cast<float>(screenHeight) });
    shader->SetFloat("brightness", brightness);
    shader->SetFloat("humidity", humidity);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_DEPTH_TEST);
}

void Skybox::SetBrightness(float b) {
    this->brightness = b;
}

void Skybox::SetHumidity(float h) {
    this->humidity = h;
}
