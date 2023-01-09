
#version 330 core
uniform sampler2D texturaL; // tipo sampler2D para texturas 2D
uniform sampler2D texturaM;
uniform float BF; // blending factor
uniform float intLuzAmb; // luz ambiente blanca
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor;

vec2 distorsion(vec2 coord){
    // Distorsion se define como f(x,y) = (sin(distancia - 0.5 * pi), cos(distancia - 0.5 * pi))

    float distancia = length(coord - vec2(0.5, 0.5));

    return vec2(sin(distancia * 3.14), cos(distancia * 3.14));
}

void main() {

    vec2 coord = vUv0 + distorsion(vUv0);

    vec3 colorL = vec3(texture(texturaL, coord)); // acceso a téxel
    vec3 colorM = vec3(texture(texturaM, vUv0)); // configuración!
    vec3 color = (colorL * colorM) * intLuzAmb;

    // color = (bFractal(coord, coord.x, coord.y, 600)) ? color : vec3(0.0, 0.0, 0.0);

    // float x = 0.299 * color.x + 0.587 * color.y + 0.114 * color.z;

    // color = vec3(x, x, x);

    fFragColor = vec4(color, 1.0); // out


}