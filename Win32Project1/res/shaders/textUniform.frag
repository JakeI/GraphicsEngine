#version 330 core

#include "text.glsl"

in vec2 textureUV;

layout (location = 0) out vec4 col;

uniform sampler2D fontAtlas;

uniform vec4 typeScalar;
uniform vec4 bodyColor;
uniform vec4 outlineColor;
uniform vec3 edges;
uniform vec4 shaddowColor;
uniform vec4 shaddowParam;
uniform vec4 backgroundColor;

void main() {

	col = textureFontColor(fontAtlas, textureUV, typeScalar,
			bodyColor, outlineColor, edges, shaddowColor, 
			shaddowParam, backgroundColor);
			
}