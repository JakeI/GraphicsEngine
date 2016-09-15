#pragma once

#include "EntityComponent.h"

class ColorComponent : public EntityComponent
{
public:

	glm::vec4 color;

	ColorComponent();
	~ColorComponent();

	void increment(float t, float dt);
	void upload(Shader* shader);
	Type getType() { return COLOR; }
};

