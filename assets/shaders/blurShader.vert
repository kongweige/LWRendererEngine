#version 430 core
layout (location = 0) in vec2 aPosNDC;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

//TODO::make this a compute shader instead, no need to go through rop
void main(){
    gl_Position = vec4(aPosNDC.x, aPosNDC.y, 0.0, 1.0);
    TexCoords = aTexCoords;
}