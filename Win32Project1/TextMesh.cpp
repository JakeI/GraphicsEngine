#include "TextMesh.h"


TextMesh::Param::Param() :
	type(FONT_STD),
	height(0.2f),
	advance(1.0f, 0.0f),
	italic(0.1f),
	lineNum(0),
	typeScalar(1.0f, 0.0f, 0.0f, 0.0f),
	position(-0.8f, 0.0f, 0.0f),
	bodyColor(0.1f, 0.1f, 0.1f, 1.0f),
	outlineColor(0.9f, 0.9f, 0.9f, 1.0f),
	edges(0.45f, 0.1f, 0.1f),
	shaddowColor(0.0f, 0.0f, 0.5f, 1.0f),
	shaddowParam(-1.0f/512.0f, -1.0f/512.0f, 0.45f, 0.50f),
	backgroundColor(0.0f, 0.0f, 0.0f, 0.0f)
{
	
}

void TextMesh::Param::upload(Shader* shader) {
	shader->uniform("typeScalar", typeScalar);
	shader->uniform("bodyColor", bodyColor);
	shader->uniform("outlineColor", outlineColor);
	shader->uniform("edges", edges);
	shader->uniform("shaddowColor", shaddowColor);
	shader->uniform("shaddowParam", shaddowParam);
	shader->uniform("backgroundColor", backgroundColor);
}

TextMesh::TextMesh(){

}


TextMesh::~TextMesh() {
	
}

void TextMesh::pack(Font* font, std::string & s) {
	param.typeScalar = font->getFontPart(param.type)->scalar;

	std::list<Mesh::Atribute> attributes;
	createAttribList(attributes);
	setLocations(attributes);

	primative = GL_QUADS;

	std::vector<Vertex> data(4 * s.size()); // not quite the right length (controll sequences are also counted)
	Param* lpParam = &param;
	glm::vec2 courser(param.position.x, param.position.y);
	glm::vec2* lpCourser = &courser;
	param.lineNum = 0.0f;
	for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
		addChar(*it, data, lpCourser, lpParam, font);
	}

	Mesh::uploadData<Vertex>(data, attributes, sizeof(Vertex)); // TODO: mape the pack type have an affect
}

void TextMesh::createAttribList(std::list<Mesh::Atribute> & attributes) {
	attributes.push_back(Mesh::Atribute(0, (int)offsetof(struct Vertex, x), 3));
	attributes.push_back(Mesh::Atribute(1, (int)offsetof(struct Vertex, u), 2));
}

void TextMesh::addChar(const char c, std::vector<Vertex> & data, glm::vec2* courser, Param* param, Font* font) {
	
	Font::FontPart* fp = font->getFontPart(param->type);

	if (c == '\n') {
		float a = param->height / fp->common.lineHeight;
		glm::vec2 b(param->advance.y, -param->advance.x);
		param->lineNum += 1.0f;
		*courser = glm::vec2(param->position.x, param->position.y) 
			+ param->lineNum * a * fp->common.lineHeight * b;
		return;
	}
	else if (c == '\t' || c == ' ') {
		Font::FontPart::Character* ch = &fp->chars[(int)c];
		float a = param->height / fp->common.lineHeight;
		*courser += a * ch->xadvancef * param->advance;
		return;
	}
	
	Font::FontPart::Character* ch = &fp->chars[(int)c];

	Vertex v[4];
	const int numv = sizeof(v) / sizeof(Vertex);

	setPositions(v, fp, ch, courser, param);
	setTextureUVs(v, ch);

	float a = param->height / fp->common.lineHeight;
	*courser += a * ch->xadvancef * param->advance;

	for (int i = 0; i < numv; i++)
		data.push_back(v[i]);
}


void TextMesh::setTextureUVs(Vertex* v, Font::FontPart::Character* ch) {
	v[3].setTextureUV(glm::vec2(ch->xf, ch->yf));
	v[2].setTextureUV(glm::vec2(ch->xf + ch->widthf, ch->yf));
	v[1].setTextureUV(glm::vec2(ch->xf + ch->widthf, ch->yf + ch->heightf));
	v[0].setTextureUV(glm::vec2(ch->xf, ch->yf + ch->heightf));
}


void TextMesh::setPositions(Vertex* v, Font::FontPart* fp, Font::FontPart::Character* ch,
		const glm::vec2* courser, const Param* param) {
	
	float a = param->height / fp->common.lineHeight;
	glm::vec3 offset(ch->xoffsetf, ch->yoffsetf, 0.0f);
	glm::vec3 vert = glm::vec3(courser->x, courser->y, 0.0f) 
		- a * offset + glm::vec3(0.0f, param->height/2.0f, 0.0f);
	glm::vec3 dx(a*ch->widthi, 0.0f, 0.0f);
	glm::vec3 dy(0.0f, -a*(ch->heighti), 0.0f);
	glm::vec3 italic = -param->italic * glm::vec3(param->advance.x, param->advance.y, 0.0f);

	v[0].setPoosition(vert + dy + italic);
	v[1].setPoosition(vert + dx + dy + italic);
	v[2].setPoosition(vert + dx);
	v[3].setPoosition(vert);

}