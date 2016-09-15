#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity(){
	for (std::map<EntityComponent::Type, ComponentRecord>::iterator it = components.begin();
			it != components.end(); ++it) {
		if (it->second.allocated) {
			delete it->second.ec;
		}
		components.erase(it);
	}
}

void Entity::add(EntityComponent* ec) {
	components[ec->getType()] = ComponentRecord(false, ec);
}

void Entity::add(const EntityComponent & ec) {
	EntityComponent* myec = new EntityComponent(ec);
	components[myec->getType()] = ComponentRecord(true, myec);
}
