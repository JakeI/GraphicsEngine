#pragma once

#include "StdAfx.h"
#include "InfoLog.h"

class Image
{
private:

	int w, h, N;
	unsigned char* data;
	
public:
	Image(const std::string & path);
	~Image();

	inline int getWidth() { return w; }
	inline int getHeight() { return h; }
	GLint getFormatGL();
	inline unsigned char & operator[](int i) { return data[i]; }
	inline bool isOpen() { return data != 0; }
};

