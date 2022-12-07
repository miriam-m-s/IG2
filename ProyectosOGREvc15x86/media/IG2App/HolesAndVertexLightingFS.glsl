
#version 330 core
uniform sampler2D corrosion; // tipo sampler2D para texturas 2D
in vec3 vFrontColor; // color de la iluminación interpolado
in vec3 vBackColor; // color de la iluminación interpolado
uniform float BF; // blending factor
uniform float intLuzAmb; // luz ambiente blanca
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor;

void main(void) {
		vec3 colorCelda = vec3(texture(corrosion, vUv0)); // acceso a téxel
		vec3 color;

		if(colorCelda.x < 0.6){
			
			if (gl_FrontFacing) color = vFrontColor * color;
			else color = vBackColor * color;

			fFragColor = vec4(color*intLuzAmb, 1.0); // out
		}

		else {
			discard;
		}

		
}