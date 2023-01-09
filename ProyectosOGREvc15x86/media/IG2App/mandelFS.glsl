
#version 330 core
uniform sampler2D texturaM;
uniform int MAXITER;
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor;
vec2 f(float a,float b){
	return vec2(a*a-b*b+vUv0.s,2*a*b+vUv0.t);
}


void main(void) {
	vec2 fu=f(0,0);
    vec3 color=vec3(0.0,0.0,0.0);
		int i=0;
		while(i<MAXITER&&((fu.x*fu.x+fu.y*fu.y)<=4)){
			fu=f(fu.x,fu.y);
			i=i+1;
		}
		if(i<MAXITER){
			color = vec3(texture(texturaM, vUv0)); // configuración!
		}
		fFragColor = vec4(color, 1.0); // out
}