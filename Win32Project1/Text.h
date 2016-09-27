#pragma once



#include "StdAfx.h"
#include "Font.h"
#include "ResourceManager.h"
#include "ModelEnity.h"
#include "TextModel.h"
#include "ConstantAnimator.h"

class Text : public ModelEntity {
private:

	const static std::string resources[];
	const static int resourcesCount;

	std::string s;

	bool isPacked;

	TextModel* getTextModel() { return (TextModel*)model; }

	ConstTextTypeScalarComp cttsc;

public:

	TextModel::Param param;

	Text();
	~Text();
	void init() override;
	void increment(float time, float deltaTime) override;
	void render(Maths::ProjView* pv, RenderMode rm) override;

	template<typename T> Text & operator<<(const T & x);
	template<> Text & operator<< <std::string>(const std::string & x);
	template<> Text & operator<< <char>(const char & x);

	void clearText();
	void remove(int index);
	int size();

	void pack();
};


template<typename T>
inline Text & Text::operator<<(const T & x) {
	isPacked = false;
	s = s + std::to_string(x);
	return *this;
}

template<>
inline Text & Text::operator<< <std::string>(const std::string & x)
{
	isPacked = false;
	s = s + x;
	return *this;
}

template<>
inline Text & Text::operator<< <char> (const char & x) {
	isPacked = false;
	s = s + x;
	return *this;
}

// lets just leve this alon for know Mayby I will need it later
/*class Text : public Mesh
{
public:

	enum PackType { STREAM, STATIC };
	enum RenderType { UNIFORM, DYNAMIC }; //upload parameters as uniforms or as attributes

private:

	const static std::string resources[];
	const static int resourcesCount; // Remove this and have a text entity do it

	class DrawParam {

	};

	class UniformDrawParam : public DrawParam {

	};

	class DynamicDrawParam : public DrawParam {
	public:
		FONT_TYPE type;
		glm::vec3 position;
		glm::vec4 bodyColor;
		glm::vec4 outlineColor;
		glm::vec3 edges;
		glm::vec4 shaddowColor;
		glm::vec4 shaddowParam;
		glm::vec4 backgroundColor;
		float height;
		DynamicDrawParam();
	};

	struct UniformVertex {
		float x, y, z; // position
		float u, v;	   // texture coordinates

		inline void setPoosition(const glm::vec3 p) { x = p.x; y = p.y; z = p.z; }
		inline void setTexxtureUV(const glm::vec2 uv) { u = uv.x; v = uv.y; }
	};

	struct DynamicVertex { // d* are dummy veriables to make access on the GPU more efficient
		float  x,  y,  z, d1; // position
		float  u,  v, d2, d3; // texture coordinates
		float tr, tg, tb, ta; // type vector
		float fr, fg, fb, fa; // character body color
		float lr, lg, lb, la; // character outline color
		float fw, fe, le, d4; // body width and and edge + outline width annd edge
		float sr, sg, sb, sa; // shaddow color
		float sx, sy, sw, se; // shadow offset and hight
		float br, bg, bb, ba; // character background color

		inline void setPosition(const glm::vec3 pos) { x = pos.x; y = pos.y; z = pos.z; }
		inline void setTextureUV(const glm::vec2 uv) { u = uv.x; v = uv.y; }
		inline void setTypeScalar(const glm::vec4 type) { tr = type.r; tg = type.g; tb = type.b; ta = type.a; }
		inline void setBodyColor(const glm::vec4 f) { fr = f.r; fg = f.g; fb = f.b; fa = f.a; }
		inline void setBodyEdges(const float width, const float edge) { fw = width; fe = edge; }
		inline void setOutlineColor(const glm::vec4 l) { lr = l.r; lg = l.g; lb = l.b; la = l.a; }
		inline void setOutlineEdge(const float edge) { le = edge; }
		inline void setShaddowColor(const glm::vec4 s) { sr = s.r; sg = s.g; sb = s.b; sa = s.a; }
		inline void setShaddowOffset(const glm::vec2 o) { sx = o.x; sy = o.y; }
		inline void setShaddowEdges(const float width, const float edge) { sw = width; se = edge; }
		inline void setBackgroundColor(const glm::vec4 b) { br = b.r; bg = b.g; bb = b.b; ba = b.a; }
	};

	std::stringstream ss;

	bool wasPacked;
	PackType packType;

	void createAttribListDynamic(std::list<Mesh::Atribute> & attributes);
	void createAttribListUniform(std::list<Mesh::Atribute> & attributes);
	void addCharUniform(const char c, std::vector<DynamicVertex> & data, DrawParam* drawParam, Font* font);
	void addCharDynamic(const char c, std::vector<DynamicVertex> & data, DynamicDrawParam* drawParam, Font* font);

	inline GLenum pttoe(PackType type);

	void packDynamic(Font* font);
	void packUniform(Font* font);

public:
	Text();
	~Text();

	template<class T>
	Text & operator<<(const T & x);

	void setPackType(PackType type) { packType = type; }

	void pack();
	void render() override;
	void render(float mousex, float mousey); // just for testing;
	void init() { // No that's really somehting the entity should do
		resm->prepareResources(resources, resourcesCount);
	}
};


// WTF this has to be placed in the header?!
template<class T>
Text & Text::operator<<(const T & x) {
	wasPacked = false;
	ss << x;
	return *this;
}*/
