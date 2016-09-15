#include "Text.h"

const std::string Text::resources[] = {
	"res/shaders/textUniform",
	"res/fonts/georgia.fnt",
};
const int Text::resourcesCount = sizeof(Text::resources) / sizeof(std::string);

Text::Text() : 
	isPacked(false) 
{

}

Text::~Text() {
	resm->releaseResources(resources, resourcesCount);
}

void Text::init() {
	resm->prepareResources(resources, resourcesCount);
}

void Text::increment(float time, float deltaTime) {

}

void Text::render(Entity::RenderMode rm) {
	switch (rm) {
	case Entity::RenderMode::PLAIN:
		{
			if (!isPacked) {
				pack();
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			Shader* shader = (Shader*)resm->getResource("res/shaders/textUniform");
			shader->use();

			shader->uniform("mvp", glm::mat4(1.0f));

			Font* font = (Font*)resm->getResource("res/fonts/georgia.fnt");
			font->texture->bind(GL_TEXTURE_2D);

			mesh.param.upload(shader);
			mesh.render();

			glBindTexture(GL_TEXTURE_2D, 0);

			glUseProgram(0);

			glDisable(GL_BLEND);
		}
		break;
	}
}

void Text::clearText() {
	s.clear();
	isPacked = false;
}

void Text::remove(int index) {
	s = s.substr(0, index) + s.substr(index + 1);
}

int Text::size() {
	return s.size();
}

void Text::pack() {
	// TODO improve this later
	
	Font* font = (Font*)resm->getResource("res/fonts/georgia.fnt");
	mesh.pack(font, s);

	isPacked = true;
}


/*
const std::string Text::resources[] = {
	"res/shaders/text",
	"res/fonts/georgia.fnt",
};
const int Text::resourcesCount = sizeof(Text::resources) / sizeof(std::string);


Text::DynamicDrawParam::DynamicDrawParam() {
	type = FONT_STD;
	position = glm::vec3(-0.8f, 0.0f, 0.0f);
	bodyColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	outlineColor = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	edges = glm::vec3(0.45, 0.1, 0.1);
	shaddowColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	shaddowParam = glm::vec4(-1.0f, -1.0f, 0.45, 0.65);
	backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	height = 0.1f;
}

Text::Text() : wasPacked(false)
{
	setPackType(STATIC);
}


Text::~Text()
{
	resm->releaseResources(resources, resourcesCount);
}


GLenum Text::pttoe(PackType type) {
	switch (type) {
	case STATIC: return GL_STATIC_DRAW;
	case STREAM: return GL_STREAM_DRAW;
	}
}


void Text::createAttribListDynamic(std::list<Mesh::Atribute> & attributes) {
	attributes.push_back(Mesh::Atribute(0, (int)offsetof(struct DynamicVertex, x), 3));
	attributes.push_back(Mesh::Atribute(1, (int)offsetof(struct DynamicVertex, u), 2));
	attributes.push_back(Mesh::Atribute(2, (int)offsetof(struct DynamicVertex, tr), 4));
	attributes.push_back(Mesh::Atribute(3, (int)offsetof(struct DynamicVertex, fr), 4));
	attributes.push_back(Mesh::Atribute(4, (int)offsetof(struct DynamicVertex, lr), 4));
	attributes.push_back(Mesh::Atribute(5, (int)offsetof(struct DynamicVertex, fw), 3));
	attributes.push_back(Mesh::Atribute(6, (int)offsetof(struct DynamicVertex, sr), 4));
	attributes.push_back(Mesh::Atribute(7, (int)offsetof(struct DynamicVertex, sx), 4));
	attributes.push_back(Mesh::Atribute(8, (int)offsetof(struct DynamicVertex, br), 4));
}

void Text::createAttribListUniform(std::list<Mesh::Atribute> & attributes) {
	
}

void Text::addCharDynamic(const char c, std::vector<DynamicVertex> & data, DynamicDrawParam* drawParam, Font* font) {
	Font::FontPart* fp = font->getFontPart(drawParam->type);
	
	DynamicVertex v[4];
	const int numv = sizeof(v) / sizeof(DynamicVertex);

	for (int i = 0; i < numv; i++) {
		v[i].setBcol(drawParam->backColor);
		v[i].setFcol(drawParam->frontColor);
		v[i].setType(fp->scalar);
	}

	Font::FontPart::Character* ch = &fp->chars[(int)c];

	float hightRatio = ch->heightf / drawParam->height;

	glm::vec3 dx(drawParam->height*ch->aspectf, 0.0f, 0.0f);
	glm::vec3 dy(0.0f, drawParam->height, 0.0f);
	glm::vec3 offset(0.0f, 0.0f, 0.0f); //TODO: make this a parameter

	glm::vec3 courser = drawParam->position + glm::vec3(hightRatio*ch->xoffsetf, -hightRatio*ch->yoffsetf, 0.0f);

	v[0].setPos(courser);
	v[1].setPos(courser + dx);
	v[2].setPos(courser + dx + dy + offset);
	v[3].setPos(courser + dy + offset);

	v[3].setUV(glm::vec2(ch->xf, ch->yf));
	v[2].setUV(glm::vec2(ch->xf + ch->widthf, ch->yf));
	v[1].setUV(glm::vec2(ch->xf + ch->widthf, ch->yf + ch->heightf));
	v[0].setUV(glm::vec2(ch->xf, ch->yf + ch->heightf));

	static const glm::vec3 advance(1.0f, 0.0f, 0.0f);

	drawParam->position += 2.0f * hightRatio * ch->xadvancef * advance;
	
	for (int i = 0; i < numv; i++)
		data.push_back(v[i]);
}

void Text::packDynamic(Font* font) {
	std::list<Mesh::Atribute> attributes;
	createAttribListDynamic(attributes);
	setLocations(attributes);

	primative = GL_QUADS;

	std::string s = ss.str();
	std::vector<DynamicVertex> data(4 * s.size()); // not quite the right length (controll sequences are also counted)
	DynamicDrawParam drawParam;
	DynamicDrawParam* drawParamPtr = &drawParam;
	for (std::string::iterator it = s.begin(); it != s.end(); ++it) {
		addCharDynamic(*it, data, drawParamPtr, font);
	}

	Mesh::uploadData<DynamicVertex>(data, attributes, sizeof(DynamicVertex)); // TODO: mape the pack type have an affect

	wasPacked = true;
}

void Text::packUniform(Font* font) {

}

void Text::pack() {
	Font* font = (Font*)resm->getResource("res/fonts/georgia.fnt");
}

void Text::render() {
	if (!wasPacked) {
		setPackType(STREAM);
		pack();
	}

	Shader* s = (Shader*)resm->getResource("res/shaders/text"); // TODO: remove this hand have the text entity do it
	s->use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	Font* font = (Font*)resm->getResource("res/fonts/georgia.fnt");
	glBindTexture(GL_TEXTURE_2D, font->texture->tbo);

	Mesh::render();

	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::render(float mousex, float mousey) {
	if (!wasPacked) {
		setPackType(STREAM);
		pack();
	}

	Shader* s = (Shader*)resm->getResource("res/shaders/text"); // TODO: remove this hand have the text entity do it
	s->use();
	s->uniform("mvp", glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 0.0f)));

	s->uniform("width", mousex);
	s->uniform("edge", mousey);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	

	Font* font = (Font*)resm->getResource("res/fonts/georgia.fnt");
	glBindTexture(GL_TEXTURE_2D, font->texture->tbo);

	Mesh::render();

	glDisable(GL_BLEND);

	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
*/
