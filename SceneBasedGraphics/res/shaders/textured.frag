#version 330 core

uniform sampler2D colorMap;

in vec2 UVs;

layout (location = 0) out vec4 col;

void main(){
	col = texture2D(colorMap, UVs);
}