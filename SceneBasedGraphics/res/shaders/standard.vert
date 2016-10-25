#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

uniform mat4 mvp = mat4(1.0);
uniform mat4 m = mat4(1.0);
uniform mat4 v = mat4(1.0);
uniform mat4 p = mat4(1.0);

out vec4 c;


void main(){
	gl_Position = mvp * vec4(position, 1.0);
	c = color;
}