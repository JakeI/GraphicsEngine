#version 330 core

#include "text.glsl"

in vec2 textureUV;
in vec4 typeScalar;
in vec4 bodyColor;
in vec4 outlineColor;
in vec3 edges;
in vec4 shaddowColor;
in vec4 shaddowParam;
in vec4 backgroundColor;

layout (location = 0) out vec4 col;

uniform sampler2D fontAtlas;


void main(){

	col = textureFontColor(fontAtlas, textureUV, typeScalar, 
			bodyColor, outlineColor, edges, shaddowColor, 
			shaddowParam, backgroundColor);
	
}