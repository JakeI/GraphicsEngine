#pragma once

#include "StdAfx.h"
#include "Mesh.h"
#include "Font.h"
#include "Shader.h"

class TextMesh :
	public Mesh
{
public:

	struct Param {
		FONT_TYPE type;
		float height;
		glm::vec2 advance;
		float italic;
		float lineNum;

		glm::vec4 typeScalar;
		glm::vec3 position;
		glm::vec4 bodyColor;
		glm::vec4 outlineColor;
		glm::vec3 edges;
		glm::vec4 shaddowColor;
		glm::vec4 shaddowParam;
		glm::vec4 backgroundColor;
		Param();
		void upload(Shader* shader);
	} param;

private:

	struct Vertex {
		float x, y, z; // position
		float u, v;	   // texture coordinates

		inline void setPoosition(const glm::vec3 p) { x = p.x; y = p.y; z = p.z; }
		inline void setTextureUV(const glm::vec2 uv) { u = uv.x; v = uv.y; }
	};

	void createAttribList(std::list<Mesh::Atribute> & attributes);
	void addChar(const char c, std::vector<Vertex> & data, glm::vec2* courser, Param* param, Font* font);
	void setTextureUVs(Vertex* v, Font::FontPart::Character* ch);
	void setPositions(Vertex* v, Font::FontPart* fp, Font::FontPart::Character* ch, 
		const glm::vec2* courser, const Param* param);

public:

	TextMesh();
	~TextMesh();

	void pack(Font* font, std::string & s);
};



