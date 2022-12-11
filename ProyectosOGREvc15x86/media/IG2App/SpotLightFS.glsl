#version 330 core
in vec2 vUv0; 
out vec4 fFragColor;

void main(void) {			
	vec3 color = {1.0,1.0,0.0};
	fFragColor = vec4(color, 1.0); 		
}