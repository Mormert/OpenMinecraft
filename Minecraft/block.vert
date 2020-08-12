#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec2 aFaceId_FaceShadow;

layout (location = 3) in vec4 instancingDataPos; // x, y, z, rot
layout (location = 4) in vec4 instancingDataFaces; // front, top, bottom, side, side, side

out vec3 FragPos;
out vec2 TexCoords;

out float shadowStrength;
flat out int face_id;
out vec4 faces;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// To do: use the rotationY cleverly to rotate the block
// using the instancingDataPos.w
mat4 rotationY(in float angle) {
	return mat4(cos(angle),		0,		sin(angle),	0,
			 			0,		1.0,			 0,	0,
				-sin(angle),	0,		cos(angle),	0,
						0, 		0,				0,	1);
}

void main()
{
    FragPos = vec3(model * vec4(aPos + instancingDataPos.xyz, 1.0));
    TexCoords = aTexCoords;

	faces = instancingDataFaces;
	face_id = int(aFaceId_FaceShadow.x) -1; // can be 0, 1, 2, 3
	shadowStrength = aFaceId_FaceShadow.y;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}