#version 330 core
uniform mat4 normalMat;
uniform mat4 modelViewProjMat;
in vec3 normal;
in vec2 uv0;
in vec4 vertex;
out vec2 vUv0;
out vec3 viewVertex;
out vec3 viewNormal;

void main() {
	viewVertex = vec3(modelViewProjMat * vertex);
	viewNormal = normalize(vec3(normalMat * vec4(normal,0)));
	vUv0=uv0;
	gl_Position = modelViewProjMat * vertex;
}