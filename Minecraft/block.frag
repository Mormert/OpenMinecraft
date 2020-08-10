#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

flat in int face_id;
in vec4 faces;

uniform sampler2D ourTexture;

void main()
{    




	int x = int(faces[face_id]) % 16;
	int y = int(faces[face_id]) / 16;

	FragColor = texture(ourTexture, TexCoords + vec2(float(x)/16.0,float(y)/16.0));

	if(FragColor.w < 0.1)
	{
		discard;
	}
}