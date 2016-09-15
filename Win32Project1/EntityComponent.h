#pragma once

#include "StdAfx.h"
#include "Shader.h"

class EntityComponent
{
public:

	enum Type {
		UNDEFINED, TRANSFORM, COLOR, 
	};

	EntityComponent();
	~EntityComponent();

	virtual void increment(float t, float dt) {}
	virtual void upload(Shader* shader) { }
	virtual Type getType() { return UNDEFINED; }
};

