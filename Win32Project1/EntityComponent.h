#pragma once

#include "StdAfx.h"

class EntityComponent
{
public:

	enum Type {
		UNDEFINED, 
		TRANSFORM2,
		TRANSFORM3,
		COLOR, 
		TYPE_SCALAR, 
		BODY_COLOR, 
		OUTLINE_COLOR, 
		DISTANCE_EDGES, 
		SHADDOW_COLOR,
		SHADDOW_PARAM,
		BACKGROUND_COLOR,
	};

	enum DType {
		NONE,
		FLOAT,
		VEC2,
		VEC3,
		VEC4,
		TRANSFORM2_DT,
		TRANSFORM3_DT
	};

	static const std::map<Type, DType> dTypeMap;
	static DType getDType(Type);

	EntityComponent();
	~EntityComponent();

	virtual void increment(float t, float dt) {}
	virtual Type getType() const { return UNDEFINED; }
	virtual void get(void* buffer) { }
};

