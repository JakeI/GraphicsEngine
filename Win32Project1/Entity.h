#pragma once

#include "StdAfx.h"
#include "Shader.h"
#include "EntityComponent.h"
#include "Maths.h"
#include "RenderMode.h"

using namespace rem;

class Entity
{

protected:
	
	std::map<EntityComponent::Type, EntityComponent*> components;

public:
	Entity();
	~Entity();

	void add(EntityComponent* ec);

	virtual void init() {}
	virtual void increment(float time, float deltaTime);
	virtual void render(Maths::ProjView* pv, RenderMode rm) {}
	virtual void uploadUniforms(Shader* shader, RenderMode rm, void* param) {}
};

