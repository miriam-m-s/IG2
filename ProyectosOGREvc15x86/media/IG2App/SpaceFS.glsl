
#version 330 core
uniform sampler2D texturaSky; // tipo sampler2D para texturas 2D
uniform sampler2D texturaMap;
uniform float intLuzAmb; // luz ambiente blanca
in vec2 vUv0; // out del vertex shader
in vec2 vUv1; // out del vertex shader
out vec4 fFragColor;

void main(void) {
		vec3 colorMap = vec3(texture(texturaMap, vUv0)); // acceso a téxel
		vec3 colorSky = vec3(texture(texturaSky, vUv1)); // configuración!
		vec3 color = colorSky* colorMap * intLuzAmb;
		fFragColor = vec4(color, 1.0); // out
}