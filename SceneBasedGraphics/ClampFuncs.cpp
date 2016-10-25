#include "ClampFuncs.h"
 

float ClampFuncs::one(float t) { return 1.0f; }
float ClampFuncs::zero(float t) { return 0.0f; }
float ClampFuncs::clmap01(float t) { return Maths::clamp(t, 0.0f, 1.0f); }
float ClampFuncs::inverseClamp01(float t) { return 1.0f - Maths::clamp(t, 0.0f, 1.0f); }
float ClampFuncs::pass(float t) { return t; }

float ClampFuncs::repeate(float t) { return t - floorf(t); }
float ClampFuncs::circular(float t) {
	t *= 2.0f;
	float f = floorf(t);
	if ((int)f % 2 == 0) return t - f;
	else return 1.0f - (t - f);
}