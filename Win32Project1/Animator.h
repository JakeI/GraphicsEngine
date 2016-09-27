#pragma once

#include "StdAfx.h"
#include "ClampFuncs.h"

template <class U>
class Animator
{
private:

	float timedOffset, timeFactor;
	float getT(float globalTime) { 
		float t = timeFactor*(globalTime - timedOffset);
		return clampFunc(t); }
	ClampFunc clampFunc;

	virtual U getValue(float t) { return U(); }

	U current;

public:
	Animator() : timedOffset(0.0f), timeFactor(1.0f), clampFunc(ClampFuncs::one), current() {}
	Animator(float start, float length, ClampFunc cf) : 
		timedOffset(start), timeFactor(1.0f/length), clampFunc(cf), current() {}
	~Animator() {}

	void setStart(float start) { timedOffset = start; }
	void setLength(float length) { timeFactor = 1.0f / length; }
	void setClampFunc(ClampFunc cf) { clampFunc = cf; }

	void getToBuffer(void* buffer) { *((U*)buffer) = get(); }

	virtual U get() { return current; } // only override this if in the ConstantAnimator class
	virtual void increment(float t, float dt) { current = getValue(getT(t)); } // only override this in the ConstantAnimator class
};

