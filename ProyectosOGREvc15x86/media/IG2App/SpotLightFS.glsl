
#version 330 core
uniform sampler2D beachStones; // tipo sampler2D para texturas 2D

uniform vec3 positionaLight; // luz ambiente blanca
uniform float a; 
uniform float b; 
uniform float st; 
in vec2 vUv0; // out del vertex shader
in vec3 viewVertex;
in vec3 viewNormal;
out vec4 fFragColor;

float diff(vec3 cVertex, vec3 cNormal)
{
	vec3 lightDir = lightPosition.xyz; // directional light ?
	if (lightPosition.w == 1) // positional light ?
	lightDir = lightPosition.xyz ‐ cVertex;

	return max(dot(cNormal, normalize(positionaLight)), 0.0);
	// dot: coseno ángulo
}

void main(void) {
		float zoom=st*(a+b);
		vec3 colorMap = vec3(texture(beachStones, vUv0)); // acceso a téxel
		vec3 color = colorSky* colorMap ;
		fFragColor = vec4(color, 1.0); // out
}