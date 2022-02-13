#version 300 es

uniform highp vec3 camdir;
uniform highp vec2 resolution;

out highp vec4 FragColor;

void main()
{
	highp vec2 uv = gl_FragCoord.xy/resolution;
	highp vec2 p = uv - 0.5;
	highp vec3 r = normalize(vec3(p, 0.9)) + camdir;

	FragColor = vec4(normalize(vec3(0.01, r.y+0.1, r.y+0.2)), 1.0);
}