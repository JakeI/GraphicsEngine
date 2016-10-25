#pragma once

#include "StdAfx.h"
#include "Shader.h"
#include "Mesh.h"
#include "Strings.h"
#include "RenderMode.h"
#include "Mdl.h"
#include "Texture.h"
#include "Resource.h"
#include "ResourceBuffer.h"
#include "ResourceManager.h"

class Entity;

using namespace rem;

// Uses the content of a Mdl class to create a Vertex Attribute array
// bind all about it properly and render it using the specified mode
class Model : public Resource {
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

	std::list<Pair> renderMap; //this will feal like a std::map but allow to search for the key (Pair.first) in whitch a spesific bit is set
	ResourceBuffer resBuffer;

protected:

	void setUp(const Mdl* mdl);

public:

	Model(const std::string & path); // constructor for loading through the resource manager
	Model(const Mdl* mdl); // can only be used after the glewInit call
	Model(); // must call the setUp or init(Mdl* mdl) method
	~Model();

	void render(RenderMode mode, Entity* componentBuffer, void* param);
	void setTexturePtr(RenderMode mode, Texture* texture);
	void setRange(RenderMode mode, int begin, int end);

	// resource functions
	static Resource* alloc(const std::string & path) { return new Model(path); }
	void init_resource(const std::string & path) override;
};