
#version 330 core
uniform sampler2D beachStones;
uniform vec4 positionaLight; // blending factor
uniform float intLuzAmb; // luz ambiente blanca
uniform float st;
uniform float a;
uniform float b;
float ZF;
in vec2 vUv0; // out del vertex shader
in vec3 viewVertex;
in vec3 viewNormal;
out vec4 fFragColor;

float diff(vec3 cVertex, vec3 cNormal)
{
    vec3 lightDir = positionaLight.xyz; 
    if (positionaLight.w == 1) 
        lightDir = positionaLight.xyz - cVertex;
    return max(dot(normalize(cNormal), normalize(lightDir)), 0.0);    // dot: coseno ángulo
}

void main(void) {
	vec3 colorCelda = vec3(texture(beachStones, vec2(vUv0.x+st, vUv0.y))); // acceso a téxel

	if(colorCelda.x < 0.6){
				ZF=st*a+b;
				float op = diff(viewVertex, viewNormal);
				vec3 color = vec3(texture(beachStones, vec2(vUv0.x+st, vUv0.y)));
	
				if(op<=ZF)
					color = vec3(texture(beachStones,  vec2(vUv0.x+st, vUv0.y)))*op*vec3(1,0.2,1); // acceso a t�xel
				else{
				   color = vec3(texture(beachStones,  vec2(vUv0.x+st, vUv0.y)))*op*vec3(0,1,1); // acceso a t�xel
				}

				fFragColor = vec4(color*intLuzAmb, 1.0); // out
		
		}
		else {
			fFragColor = vec4(vec3(0,st/2+0.5,st/2+0.5), 1.0); // out
		}
	
}