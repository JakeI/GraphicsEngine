#pragma once
#include "EntityComponent.h"

class Transform : public EntityComponent
{
public:
	Transform();
	~Transform();

	virtual glm::mat4 createMatrix() { return glm::mat4(1.0f); }
	Type getType() { return TRANSFORM; }
};

