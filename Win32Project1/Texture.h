#pragma once

#include "StdAfx.h"
#include "InfoLog.h"
#include "Image.h"
#include "Strings.h"

class Texture
{
private:

	class TexParameter {
	private:

		static void setFilter(GLint* filter, const std::string & value);
		void handel(const std::string & key, const std::string & value);

	public:

		GLint wrapT;
		GLint wrapS;
		GLint magFilter;
		GLint minFilter;

		std::string path;

		TexParameter();

		void read(const std::string & path);
	};

	static GLuint loadToTBO(const TexParameter* param);

public:

	GLuint tbo;

	Texture(const std::string & path);
	~Texture();

	void bind(GLenum target = GL_TEXTURE_2D);
};

