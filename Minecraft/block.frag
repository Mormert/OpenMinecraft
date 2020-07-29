#version 330 core
out vec4 FragColor;

in vec3 FragPos;

void main()
{    

    FragColor = vec4(FragPos, 1.0);
	
}