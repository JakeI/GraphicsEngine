#include "Entity.h"


Entity::Entity()
{
}


Entity::~Entity(){
	components.clear();
}

void Entity::add(EntityComponent* ec) {
	components[ec->getType()] = ec;
}

void Entity::increment(float time, float deltaTime) {
	for (auto pair : components)
		pair.second->increment(time, deltaTime);
}