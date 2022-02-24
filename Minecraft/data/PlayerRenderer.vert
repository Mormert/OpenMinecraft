#version 300 es
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;

out vec3 fillColor;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    fillColor = color;
}