#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 mvp;
uniform vec4 color;

out vec4 c;


void main(){
	gl_Position = mvp * vec4(position, 1.0);
	c = color;
}