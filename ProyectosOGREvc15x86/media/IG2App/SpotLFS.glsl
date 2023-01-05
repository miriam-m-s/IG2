
#version 330 core
uniform sampler2D beachStones;
uniform vec4 positionaLight; // blending factor
uniform float intLuzAmb; // luz ambiente blanca
uniform float st;
uniform float a;
uniform float b;
float ZF;
in vec2 vUv0; // out del vertex shader
in vec3 viewVertex;
in vec3 viewNormal;
out vec4 fFragColor;

float diff(vec3 cVertex, vec3 cNormal)
{
    vec3 lightDir = positionaLight.xyz; 
    if (positionaLight.w == 1) 
        lightDir = positionaLight.xyz - cVertex;
    return max(dot(normalize(cNormal), normalize(lightDir)), 0.0);    // dot: coseno ángulo
}

void main(void) {
	ZF=st*a+b;
	float op = diff(viewVertex, viewNormal);
	vec3 color = vec3(texture(beachStones, vUv0));
	
	if(op <= ZF)
		color = vec3(texture(beachStones, vUv0))*0.2; // acceso a t�xel

	fFragColor = vec4(color*intLuzAmb, 1.0); // out
}