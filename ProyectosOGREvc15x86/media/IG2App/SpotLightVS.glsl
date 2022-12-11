#version 330 core
in vec2 uv0;
in vec4 vertex;
in vec3 normal;
out vec2 vUv0;
out vec3 viewVertex;
out vec3 viewNormal;
uniform mat4 normalMat;
uniform mat4 modelViewProjMat;

	void main() {
		viewVertex = vec3(modelViewProjMat * vertex);
		viewNormal = normalize(vec3(normalMat * vec4(normal,0)));
		vUv0=uv0;
		gl_Position = modelViewProjMat * vertex;
	}