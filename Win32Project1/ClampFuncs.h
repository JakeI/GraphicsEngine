#pragma once

#include "StdAfx.h"
#include "Maths.h"

typedef float (*ClampFunc)(float);

namespace ClampFuncs
{
	float one(float t);
	float zero(float t);
	float clmap01(float t);
	float inverseClamp01(float t);
	float pass(float t);
	
	float repeate(float t);
	float circular(float t);
};

