#version 300 es
out highp vec4 FragColor;

in highp vec3 fillColor;

void main()
{
    FragColor = vec4(fillColor, 1.0);
}