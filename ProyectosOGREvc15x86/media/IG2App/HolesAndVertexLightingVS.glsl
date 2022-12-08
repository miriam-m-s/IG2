#version 330 core
in vec2 uv0;
in vec4 vertex;
in vec3 normal;
out vec2 vUv0;
out vec3 vFrontColor; // color de la iluminaci�n interpolado
out vec3 vBackColor; // color de la iluminaci�n interpolado
uniform vec3 frontMaterial;
uniform vec3 backMaterial;
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform mat4 normalMat;
uniform mat4 modelViewProjMat;

float diff(vec3 cVertex, vec3 cNormal)
{
	vec3 lightDir = lightPosition.xyz; // directional light
	if (lightPosition.w == 1) // positional light
		lightDir = lightPosition.xyz - cVertex;
	return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {
	// diffuse en view space
	vec3 viewVertex = vec3(modelViewProjMat * vertex);
	vec3 viewNormal = normalize(vec3(normalMat * vec4(normal,0)));

	vec3 diffuse = diff(viewVertex, viewNormal) * lightDiffuse * frontMaterial;
	vFrontColor = diffuse; // + specular

	diffuse = diff(viewVertex, -viewNormal) * lightDiffuse * backMaterial;
	vBackColor =  diffuse; // + specular

	vUv0 = uv0;
	gl_Position = modelViewProjMat * vertex;
}

