#include "Image.h"

namespace stb {
	#define STB_IMAGE_IMPLEMENTATION
	#include "stb_image.h"
}

Image::Image(const std::string & path){
	data = stb::stbi_load(path.c_str(), &w, &h, &N, 0);
	if (data == 0)
		ilog->printError("couldn't load image form: '" + path + "'");
}


Image::~Image() {
	if (data != 0)
		delete[] data;
}

GLint Image::getFormatGL() {
	switch (N) {
	case 1:
		return GL_LUMINANCE;
	case 2:
		return GL_LUMINANCE_ALPHA;
	case 3:
		return GL_RGB;
	case 4:
		return GL_RGBA;
	}
}
