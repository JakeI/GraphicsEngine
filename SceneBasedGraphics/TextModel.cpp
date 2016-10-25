#include "TextModel.h"


TextModel::Param::Param() :
	type(FONT_STD),
	height(0.2f),
	advance(1.0f, 0.0f),
	italic(0.0f),
	lineNum(0),
	position(0.0f, 0.0f, 0.0f)
{}

TextModel::TextModel() {
	
}

TextModel::~TextModel() {
	
}

void TextModel::init() {
	Mdl mdl;

	std::string shaderPath = "res/shaders/textUniform";
	Mdl::Stage full(FULL, GL_QUADS, ResourceRef(shaderPath), ResourceRef(nullptr), 0, 0);
	Mdl::MeshLayout fullLayout(ResourceRef(&mesh), sizeof(Vertex));
	fullLayout.atributes.push_back(Mdl::Atribute(0, (int)offsetof(struct Vertex, x), 3));
	fullLayout.atributes.push_back(Mdl::Atribute(1, (int)offsetof(struct Vertex, u), 2));
	full.meshLayouts.push_back(fullLayout);
	mdl.stages.push_back(full);

	// TODO: add a Uniform Stage

	setUp(&mdl);
}

void TextModel::pack(Font::FontPart* fp, Param* p, std::string & s) {

	std::vector<Vertex> data;//(4 * s.size()); // not quite the right length (controll sequences are also counted)
	glm::vec2 courser(p->position.x, p->position.y);
	glm::vec2* lpCourser = &courser;
	p->lineNum = 0.0f;
	for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
		addChar(*it, data, lpCourser, p, fp);
	}

	mesh.uploadData<Vertex>(data, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW); // TODO: pick the appropriate usage type
	setRange(FULL, 0, data.size());

	// TODO: make this redudant
	ModeRenderParam* m = &Model::find(FULL, renderMap)->second;
	glBindVertexArray(m->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(int)offsetof(struct Vertex, x));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(int)offsetof(struct Vertex, u));
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

void TextModel::addChar(const char c, std::vector<Vertex> & data, glm::vec2* courser, Param* param, Font::FontPart* fp) {

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


void TextModel::setTextureUVs(Vertex* v, Font::FontPart::Character* ch) {
	v[3].setTextureUV(glm::vec2(ch->xf, ch->yf));
	v[2].setTextureUV(glm::vec2(ch->xf + ch->widthf, ch->yf));
	v[1].setTextureUV(glm::vec2(ch->xf + ch->widthf, ch->yf + ch->heightf));
	v[0].setTextureUV(glm::vec2(ch->xf, ch->yf + ch->heightf));
}


void TextModel::setPositions(Vertex* v, Font::FontPart* fp, Font::FontPart::Character* ch,
		const glm::vec2* courser, const Param* param) {
	
	float a = 0.8f * (param->height / fp->common.lineHeight);
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