#pragma once

#include "StdAfx.h"
#include "Mesh.h"
#include "Font.h"
#include "Shader.h"
#include "Model.h"

class TextModel : public Model
{
public:

	struct Param {
		FONT_TYPE type;
		float height;
		glm::vec2 advance;
		float italic;
		float lineNum;
		glm::vec3 position;

		Param();
	};

private:

	Mesh mesh;

	struct Vertex {
		float x, y, z; // position
		float u, v;	   // texture coordinates

		inline void setPoosition(const glm::vec3 p) { x = p.x; y = p.y; z = p.z; }
		inline void setTextureUV(const glm::vec2 uv) { u = uv.x; v = uv.y; }
	};

	void addChar(const char c, std::vector<Vertex> & data, glm::vec2* courser, Param* param, Font::FontPart* fp);
	void setTextureUVs(Vertex* v, Font::FontPart::Character* ch);
	void setPositions(Vertex* v, Font::FontPart* fp, Font::FontPart::Character* ch, 
		const glm::vec2* courser, const Param* param);

public:

	TextModel();
	~TextModel();

	void init();

	void pack(Font::FontPart* fp, Param* p, std::string & s);
};



