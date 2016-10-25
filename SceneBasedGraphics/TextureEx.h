#pragma once
#include "Texture.h"


// TextureEx stores a normal texture but keeps some information like the resolution and format in RAM
// so this stays acsessable to the program
class TextureEx : public Texture
{
private:

	GLuint loadToTBO(const TexParameter* param) override;

	int width, height;
	GLint format;

public:

	int getWidth() const { return width; }
	int getHight() const { return height; }
	int getFormatGL() const { return format; }

	TextureEx(const std::string & path);
	~TextureEx();
};

