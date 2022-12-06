
#version 330 core
uniform sampler2D corrosion; // tipo sampler2D para texturas 2D
uniform sampler2D bumbyMetal;
uniform sampler2D beachStones;
uniform float BF; // blending factor
uniform float intLuzAmb; // luz ambiente blanca
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor;


void main(void) {
		vec3 colorCelda = vec3(texture(corrosion, vUv0)); // acceso a t�xel
		vec3 color;

		if(colorCelda.x < 0.6){
			if(gl_FrontFacing)
				 color = vec3(texture(bumbyMetal, vUv0)); // configuraci�n!
			else color = vec3(texture(beachStones, vUv0)); // configuraci�n!

			fFragColor = vec4(color*intLuzAmb, 1.0); // out
		}
		else {
			fFragColor = vec4(color*intLuzAmb,0.0); // out
		
		}

		
}