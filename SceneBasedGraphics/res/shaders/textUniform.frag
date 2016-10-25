#version 330 core

#include "text.glsl"

in vec2 textureUV;

layout (location = 0) out vec4 col;

uniform sampler2D fontAtlas;

uniform vec4 typeScalar = vec4(1.0, 0.0, 0.0, 0.0);
const vec4 bodyColor = vec4(1.0, 1.0, 0.0, 1.0);
const vec4 outlineColor = vec4(0.0, 0.0, 0.0, 1.0);
const vec3 distanceEdges = vec3(0.45, 0.1, 0.1); // distanceEdges.x = body_width; distanceEdges.y = body_edge_width; distanceEdges.z = outline_width
const vec4 shaddowColor = vec4(0.0, 0.0, 0.0, 0.0);
const vec4 shaddowParam = vec4(-1.0, -1.0, 0.45, 0.65); // a_shaddowParam.xy = shaddow_offset; a_shaddowParam.z = shaddow_width; a_shaddowParam.w = shaddow_edge_width
const vec4 backgroundColor = vec4(0.0, 0.0, 0.0, 0.0);

void main() {

	col = textureFontColor(fontAtlas, textureUV, typeScalar,
			bodyColor, outlineColor, distanceEdges, shaddowColor, 
			shaddowParam, backgroundColor);		
}