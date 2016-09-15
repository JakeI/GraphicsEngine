#version 330 core

layout (location = 0) in vec3 position;
layout (location = 3) in vec2 uvs;

uniform mat4 mvp = mat4(1.0);

out vec2 UVs;


void main(){
	gl_Position = mvp * vec4(position, 1.0);
	UVs = uvs;
}