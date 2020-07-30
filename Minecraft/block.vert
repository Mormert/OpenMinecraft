#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

// x, y, z, block_id
layout (location = 2) in vec4 instancingData;

out vec3 FragPos;
out vec2 TexCoords;

flat out int block_id;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos + instancingData.xyz, 1.0));
    TexCoords = aTexCoords;

	block_id = int(instancingData.a);
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}