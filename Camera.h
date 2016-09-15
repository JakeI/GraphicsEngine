#pragma once

#include "StdAfx.h"

class Camera
{
public:
	Camera();
	~Camera();

	virtual glm::mat4 getView() { return glm::mat4(1.0f); }
};

