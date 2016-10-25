#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_textureUV;

uniform mat4 mvp = mat4(1.0f);

out vec2 textureUV;

void main() {
	gl_Position = mvp * vec4(a_position, 1.0f);
	
	textureUV = a_textureUV;
}