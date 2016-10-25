#include "TextureEx.h"



TextureEx::TextureEx(const std::string & path) : 
	Texture()
{
	Texture::load(path);
}


TextureEx::~TextureEx()
{
}

GLuint TextureEx::loadToTBO(const TexParameter* param) {
	
	Image img(param->path);

	width = img.getWidth();
	height = img.getHeight();
	format = img.getFormatGL();

	return uploadToTBO(&img, param);
}
