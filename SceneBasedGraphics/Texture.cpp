#include "Texture.h"


Texture::TexParameter::TexParameter() {
	this->wrapS = GL_REPEAT;
	this->wrapT = GL_REPEAT;
	this->magFilter = GL_LINEAR;
	this->minFilter = GL_LINEAR;
	
	this->path = "";
}

void Texture::TexParameter::read(const std::string & path) {
	std::ifstream in(path, std::ios::in);

	if (in.is_open()) {

		std::string line;

		while (getline(in, line)) {

			if (line == "" || line[0] == '#')
				continue;

			std::stringstream ss(line);
			std::string key, value;
			getline(ss, key, '=');
			getline(ss, value);

			if (key.find("File") != std::string::npos)
				this->path = Strings::pathInSameDir(path, Strings::stripQuotes(value));
			else
				handel(key, value);

		}

	}

	in.close();
}

void Texture::TexParameter::handel(const std::string & key, const std::string & value) {
	if (key.find("MagFilter") != std::string::npos) setFilter(&magFilter, value);
	else if (key.find("MinFilter") != std::string::npos) setFilter(&minFilter, value);
	else ilog->printError("Undefined Texture controll (key='" + key + "', value='" + value + "')");
}

void Texture::TexParameter::setFilter(GLint* filter, const std::string & value) {
	if (value.find("NEAREST") != std::string::npos) *filter = GL_NEAREST;
	else if (value.find("LINEAR") != std::string::npos) *filter = GL_LINEAR;
	else ilog->printError("Undefined Filter value: '" + value + "'");
}

Texture::Texture() :
	Resource(resReg->getResTypeByKey("textures"))
{

}

Texture::Texture(const std::string & path) :
	Resource(resReg->getResTypeByKey("textures"))
{
}

void Texture::init_resource(const std::string & path) {
	load(path);
}

void Texture::load(const std::string & path) {
	
	TexParameter param;
	param.path = path;

	if (path.find(".txi") == (path.size() - 4))
		param.read(path);

	tbo = loadToTBO(&param);

}


Texture::~Texture() {
	if(wasInitialized)
		glDeleteTextures(1, &tbo);
}

GLuint Texture::uploadToTBO(const Image* img, const TexParameter* param) {

	if (img->isOpen()) {

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		GLuint tbo = 0;

		glGenTextures(1, &tbo);
		glBindTexture(GL_TEXTURE_2D, tbo);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param->wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param->wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param->magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param->minFilter);

		GLint format = img->getFormatGL();
		GLsizei width = img->getWidth(), hight = img->getHeight();
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, hight,
			0, format, GL_UNSIGNED_BYTE, &img->operator[](0));

		glBindTexture(GL_TEXTURE_2D, 0);

		return tbo;

	}

	return 0;

}

GLuint Texture::loadToTBO(const TexParameter* param) {
	
	Image img(param->path);
	return uploadToTBO(&img, param);
	
}

void Texture::bind(GLenum target) {
	glBindTexture(target, tbo);
}

