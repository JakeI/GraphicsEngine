#pragma once

#include "StdAfx.h"
#include "InfoLog.h"
#include "Resource.h"

typedef int ATRIBUTE_MASK;
#define ATRIBUTE_NONE_BIT		0x0
#define ATRIBUTE_POSITION_BIT	0x2
#define ATRIBUTE_POSITION	0
#define ATRIBUTE_COLOR_BIT		0x4
#define ATRIBUTE_COLOR		1
#define ATRIBUTE_NORMAL_BIT		0x8
#define ATRIBUTE_NORMAL		2
#define ATRIBUTE_TEXTURE_BIT	0x16
#define ATRIBUTE_TEXTURE		3

#define ATRIBUTE_OPTION_COUNT	4

class Mesh : public Resource
{
private:

	void readData(std::ifstream & in, std::vector<float> & data);
	void readTarget(std::string & line, GLenum* result);

public:

	template<class T>
	void uploadData(const std::vector<T> & data, GLenum target = GL_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW);

	GLuint vbo;
	GLenum target;
	int size; // in 4 byte blocks

	inline void bind() { glBindBuffer(target, vbo); }

	Mesh(const std::string & path);
	Mesh();
	~Mesh();

	// fetures of the resource
	void init_resource(const std::string & path) override;
	static Resource* alloc(const std::string & path) { return new Mesh(path); }
};



// For some reason this only works if its in the header file
template<class T>
void Mesh::uploadData(const std::vector<T> & data, GLenum target, GLenum usage) {

	if (data.size() == 0) {
		size = 0;
		return;
	}

	size = data.size() * sizeof(T);

	if (vbo == 0) {
		glGenBuffers(1, &vbo);
		glBindBuffer(target, vbo);
	}
	else {
		glBindBuffer(target, vbo);
		// maybe the buffer needs to be cleared somehow???
	}

	glBufferData(target, size, &data[0], usage);

	// TODO: make this more efficient using glBufferSubData to send aditional data and only rarly allocate memory with glBufferData

	glBindBuffer(target, 0);
}



