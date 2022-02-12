#version 330 core

uniform vec3 camdir;
uniform vec2 resolution;

out vec4 FragColor;

void main()
{
	vec2 uv = gl_FragCoord.xy/resolution;
	vec2 p = uv - 0.5;
	vec3 r = normalize(vec3(p, 0.9)) + camdir;

	FragColor = vec4(normalize(vec3(0.01, r.y+0.1, r.y+0.2)), 1.0);
}