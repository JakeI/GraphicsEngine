#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_textureUV;
layout (location = 2) in vec4 a_typeScalar;
layout (location = 3) in vec4 a_bodyColor;
layout (location = 4) in vec4 a_outlineColor;
layout (loaction = 5) in vec3 a_edges; // a_edges.x = body_width; a_edges.y = body_edge_width; a_edges.z = outline_width
layout (location = 6) in vec4 a_shaddowColor;
layout (location = 7) in vec4 a_shaddowParam; // a_shaddowParam.xy = shaddow_offset; a_shaddowParam.z = shaddow_width; a_shaddowParam.w = shaddow_edge_width
layout (location = 8) in vec4 a_backgroundColor;


uniform mat4 mvp = mat4(1.0f);

out vec2 textureUV;
out vec4 typeScalar;
out vec4 bodyColor;
out vec4 outlineColor;
out vec3 edges;
out vec4 shaddowColor;
out vec4 shaddowParam;
out vec4 backgroundColor;

void main(){
	gl_Position = mvp * vec4(a_position, 1.0f);
	
	textureUV = a_textureUV;
	bodyColor = a_bodyColor;
	outlineColor = a_outlineColor;
	edges = a_edges;
	shaddowColor = a_shaddowColor;
	shaddowParam = a_shaddowParam;
	backgroundColor = a_backgroundColor;
}