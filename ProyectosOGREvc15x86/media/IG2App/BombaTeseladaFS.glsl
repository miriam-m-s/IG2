
#version 330 core
uniform sampler2D texturaChecker; // tipo sampler2D para texturas 2D
uniform sampler2D texturaSky;
uniform sampler2D texturaBumpy;
uniform float BF; // blending factor
uniform float intLuzAmb; // luz ambiente blanca
in vec2 vUv0; // out del vertex shader
in vec2 vUv1; // out del vertex shader
out vec4 fFragColor;

void main(void) {
		vec3 colorCelda = vec3(texture(texturaChecker, vUv0)); // acceso a téxel
		vec3 blanco = vec3(1.0,1.0,1.0);
		vec3 color;

		if(colorCelda == blanco){
			 color = vec3(texture(texturaBumpy, vUv0)); // configuración!
		}

		else color = vec3(texture(texturaSky, vUv1)); // configuración!

		fFragColor = vec4(color*intLuzAmb, 1.0); // out
}