#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

flat in int block_id;

uniform sampler2D ourTexture;

void main()
{    

	int x = block_id % 16;
	int y = block_id / 16;

    FragColor = texture(ourTexture, TexCoords + vec2(float(x)/16.0,float(y)/16.0));
	
}