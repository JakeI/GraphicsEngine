#include "EntityComponent.h"



EntityComponent::EntityComponent()
{
}


EntityComponent::~EntityComponent()
{
}

const std::map<EntityComponent::Type, EntityComponent::DType> EntityComponent::dTypeMap = {
	{ Type::UNDEFINED, DType::NONE },
	{ Type::TRANSFORM2, DType::TRANSFORM2_DT },
	{ Type::TRANSFORM2, DType::TRANSFORM3_DT },
	{ Type::COLOR, DType::VEC4 },
	{ Type::TYPE_SCALAR, DType::VEC4 },
	{ Type::BODY_COLOR, DType::VEC4 },
	{ Type::OUTLINE_COLOR, DType::VEC4 },
	{ Type::DISTANCE_EDGES, DType::VEC3 },
	{ Type::SHADDOW_COLOR, DType::VEC4 },
	{ Type::SHADDOW_PARAM, DType::VEC4 },
	{ Type::BACKGROUND_COLOR, DType::VEC4 }
};

EntityComponent::DType EntityComponent::getDType(EntityComponent::Type t) {
	std::map<Type, DType>::const_iterator it = dTypeMap.find(t);
	if (it != dTypeMap.end())
		return it->second;
	else
		return DType::NONE;
}
