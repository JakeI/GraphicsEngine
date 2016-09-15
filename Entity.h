#pragma once

#include "StdAfx.h"
#include "EntityComponent.h"

class Entity
{
private:
	
	struct ComponentRecord { 
		bool allocated; 
		EntityComponent* ec; 
		ComponentRecord(bool allocated, EntityComponent* ec) { this->allocated = allocated; this->ec = ec; }
	};
	std::map<EntityComponent::Type, ComponentRecord> components;

public:
	Entity();
	~Entity();

	void add(EntityComponent* ec);
	void add(const EntityComponent & ec);

	virtual void init() {}
	virtual void increment(float time, float deltaTime) {}
	enum RenderMode { PLAIN };
	virtual void render(RenderMode rm = PLAIN) {}
};

