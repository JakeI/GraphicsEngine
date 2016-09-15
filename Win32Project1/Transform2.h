#pragma once
#include "Transform.h"

class Transform2 : public Transform
{
public:

	glm::vec2 translation;
	glm::vec2 scale;
	float rotation;

	Transform2();
	~Transform2();

	glm::mat4 createMatrix();
	
};

