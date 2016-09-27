#pragma once

#include "StdAfx.h"
#include "Shader.h"
#include "Mesh.h"
#include "Strings.h"
#include "RenderMode.h"
#include "Mdl.h"
#include "Texture.h"
#include "ResourceGetter.h"

class Entity;

using namespace rem;

class Model {
protected: //private: this should and will be private again

	struct ModeRenderParam {
		GLenum primative;
		Shader* shader;
		Texture* texture;
		int begin, end;
		GLuint vao;
		std::list<int> usedLocations;
		ModeRenderParam() : primative(GL_TRIANGLE_STRIP), shader(nullptr), texture(nullptr), begin(0), end(0), vao(0) {}
		void setRange(int b, int e) { begin = b; end = e; }
	};

	struct Pair {
		RenderMode first;
		ModeRenderParam second;
		Pair() : first(rem::UNDEFINED), second() {}
	};

	static std::list<Pair>::iterator find(RenderMode mode_bit, std::list<Pair> & list) { // Seach for a pari with a matching bit in the render mode
		for (std::list<Pair>::iterator it = list.begin(); it != list.end(); ++it) 
			if (it->first & mode_bit) return it;
		return list.end();
	}

	std::list<Pair> renderMap; //this will feal like a std::map but a allow to search for the key (Pair.first) with a spesific bit set
	ResourceGetter resGet;

protected:

	void setUp(const Mdl* mdl);

public:

	Model(const std::string & path);
	Model(const Mdl* mdl);
	Model(); // must call the setUp method
	~Model();

	void render(RenderMode mode, Entity* componentBuffer, void* param);
	void setTexturePtr(RenderMode mode, Texture* texture);
	void setRange(RenderMode mode, int begin, int end);
};