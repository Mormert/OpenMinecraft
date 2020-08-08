#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in float aFaceId;

layout (location = 3) in vec4 instancingDataPos; // x, y, z, rot
layout (location = 4) in vec4 instancingDataFaces; // front, top, bottom, side, side, side

out vec3 FragPos;
out vec2 TexCoords;

flat out int face_id;
out vec4 faces;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos + instancingDataPos.xyz, 1.0));
    TexCoords = aTexCoords;


	faces = instancingDataFaces;
	face_id = int(aFaceId); // can be 0, 1, 2, 3
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}