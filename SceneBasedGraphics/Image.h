#pragma once

#include "StdAfx.h"
#include "InfoLog.h"

// Stroes an Image in RAM (uses stb_image to load the image file)
class Image
{
private:

	int w, h, N;
	unsigned char* data;
	
public:
	Image(const std::string & path);
	~Image();

	inline int getWidth() const { return w; }
	inline int getHeight() const { return h; }
	GLint getFormatGL() const;
	inline unsigned char & operator[](int i) const { return data[i]; } // TODO: do range chacking
	inline bool isOpen() const { return data != 0; }
};

