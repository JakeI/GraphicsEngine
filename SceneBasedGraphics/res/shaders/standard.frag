#version 330 core

in vec4 c;

layout (location = 0) out vec4 col;

void main(){
	col = c;
}