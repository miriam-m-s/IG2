
#version 330 core
uniform sampler2D corrosion; // tipo sampler2D para texturas 2D
uniform sampler2D bumbyMetal;
uniform sampler2D beachStones;
uniform vec3 frontMaterial;
uniform vec3 backMaterial;
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
in vec2 vUv0; // out del vertex shader
in vec3 viewVertex;
in vec3 viewNormal;
out vec4 fFragColor;


float diff(vec3 cVertex, vec3 cNormal)
{
	vec3 lightDir = lightPosition.xyz; // directional light
	if (lightPosition.w == 1) // positional light
		lightDir = lightPosition.xyz - cVertex;
	return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main(void) {
		vec3 colorCelda = vec3(texture(corrosion, vUv0)); // acceso a téxel
		vec3 color;

		if(colorCelda.x < 0.6){
			
			if(gl_FrontFacing)
				 color = vec3(texture(bumbyMetal, vUv0))* diff(viewVertex, viewNormal) * lightDiffuse * frontMaterial;
			else color = vec3(texture(beachStones, vUv0))*diff(viewVertex, -viewNormal) * lightDiffuse * backMaterial;// configuración!

			fFragColor = vec4(color, 1.0); // out
		}
		else {
			discard;
		}

		
}