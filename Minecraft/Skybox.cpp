#include "Skybox.h"

#include <glad/glad.h>

Skybox::Skybox(const char* vertexShader, const char* fragmentShader)
{
	shader = new Shader(vertexShader, fragmentShader);


	constexpr float vertices[] = {
		-1.0f,-1.0f, // triangle 1
		1.0f, -1.0f,
		1.0f, 1.0f,
		1.0f,1.0f, // triangle 2
		-1.0f, 1.0f,
		-1.0f, -1.0f
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

void Skybox::Render()
{

	glDisable(GL_DEPTH_TEST);

	shader->Use();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnable(GL_DEPTH_TEST);
}