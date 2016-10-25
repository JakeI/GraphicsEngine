#pragma once

#include "StdAfx.h"
#include "InfoLog.h"
#include "Image.h"
#include "Strings.h"
#include "Resource.h"

// saves refrences to a textexture strored in graphics memory
// Is constructed from eithger an image fiel (in which case default wrap and filter functions are used)
// or from a *.txi file wich constanes the refrence of the corresponding image file and sets the wrap and filter functions
class Texture : public Resource
{
protected:

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

	static GLuint uploadToTBO(const Image* img, const TexParameter* param);
	void load(const std::string & path);

private:

	// this is called in the Texture(const std::string & path) constructor hence if it is overridden, 
	// the Texture() konstructor must be called and the load method must be used to load from file
	virtual GLuint loadToTBO(const TexParameter* param);

public:

	GLuint tbo; // TODO: make this non-public

	Texture(); // Only for inheriting types the protected load method must be called if this constructor is used
	Texture(const std::string & path); // expects a call to init(path) (used by the resourcemanager)
	~Texture();

	void bind(GLenum target = GL_TEXTURE_2D);

	// Resource features
	static Resource* alloc(const std::string & path) { return new Texture(path); }
	void init_resource(const std::string & path) override;

};

