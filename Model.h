#pragma once

#include "StdAfx.h"
#include "Shader.h"
#include "Mesh.h"

typedef void(*shaderUniformLoader)(Shader*, void*);

class Model {
protected:

	struct Atribute {
		int attrib;
		int start;
		int dim;
		Atribute() { attrib = -1; start = -1; dim = -1; }
		Atribute(int attrib, int start, int dim);
		void set(int attrib, int start, int dim);
		inline bool isUsed() { return attrib != -1 && start != -1 && dim != -1; }
	};

private:

	std::string shader;
	std::list<std::string> meshs;

	void load(const std::string & path);

	void readPrimativeType(std::ifstream & in);
	void readLayoutLine(std::ifstream & in, std::list<Atribute> & atributes, int* stride);

	GLuint vao;
	GLenum primative;

	std::list<int> locations;
	void setLocations(const std::list<Atribute> & atributes);

public:

	Model();
	~Model();

	static Model* readMdl(const std::string & path);

	void render(shaderUniformLoader sul, void* data);
};