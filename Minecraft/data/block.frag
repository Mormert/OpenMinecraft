#version 300 es
out highp vec4 FragColor;

in highp vec3 FragPos;
in highp vec2 TexCoords;
in highp vec3 ViewPosition;

in highp float shadowStrength;
flat in int face_id;
in highp vec4 faces;

uniform highp float humidity;
uniform highp float brightness;

uniform sampler2D ourTexture;

void main()
{    

	int x = int(faces[face_id]) % 16;
	int y = int(faces[face_id]) / 16;

	FragColor = texture(ourTexture, TexCoords + vec2(float(x)/16.0,float(y)/16.0));
	FragColor.xyz *= shadowStrength;

	#define LOG2 1.442695

	highp float fogDistance = length(ViewPosition);
	highp float fogDensity = humidity;
	highp float fogAmount = 1. - exp2(-fogDensity * fogDensity * fogDistance * fogDistance * LOG2);
	fogAmount = clamp(fogAmount, 0., 1.);

	FragColor = mix(FragColor, vec4(1.0, 1.0, 1.0, 1.0), fogAmount);

	FragColor.xyz *= brightness;

	if(FragColor.w < 0.1)
	{
		discard;
	}
}