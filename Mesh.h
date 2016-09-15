#pragma once

#include "StdAfx.h"
#include "InfoLog.h"

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

class Mesh
{
private:

	void load(const std::string & path);

	
	void readData(std::ifstream & in, std::vector<float> & data);

protected:

	GLuint vbo;
	int count;

	template<class T>
	void uploadData(const std::vector<T> & data, const std::list<Atribute> & atributes, const int stride, GLenum usage = GL_STATIC_DRAW);

public:
	Mesh();
	~Mesh();

	static Mesh* readMesh(const std::string & path);
};



// For some reason this only works if its in the header file
template<class T>
void Mesh::uploadData(const std::vector<T> & data, const std::list<Atribute> & atributes, const int stride, GLenum usage) {

	if (data.size() == 0) {
		count = 0;
		return;
	}

	const int countPdata = stride / sizeof(T);
	count = data.size() / countPdata;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(T), &data[0], usage);

	for (auto atribute : atributes)
		glEnableVertexAttribArray(atribute.attrib);

	for (auto atribute : atributes)
		glVertexAttribPointer(atribute.attrib, atribute.dim, GL_FLOAT, GL_FALSE,
			stride, (void*)(atribute.start));

	for (auto atribute : atributes)
		glDisableVertexAttribArray(atribute.attrib);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}



