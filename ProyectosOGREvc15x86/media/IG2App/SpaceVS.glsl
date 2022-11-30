#version 330 core
in vec2 uv0;
in vec4 vertex;
out vec2 vUv0;
out vec2 vUv1;
uniform float ZF;
uniform mat4 modelViewProjMat;

	void main() {
		vUv0=uv0;
		vUv1.s = (uv0.s - 0.5)* ZF + 0.5;
		vUv1.t= (uv0.t - 0.5)* ZF + 0.5;
		gl_Position = modelViewProjMat * vertex;
	}