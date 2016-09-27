#pragma once

#include "ModelEnity.h"
#include "ResourceGetter.h"

class ImageEntity : public ModelEntity
{
private:

	ResourceGetter resGet;

public:
	ImageEntity();

	~ImageEntity();


};

