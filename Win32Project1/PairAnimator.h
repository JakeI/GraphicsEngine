#pragma once
#include "Animator.h"
#include "InterpolationFuncs.h"

template <class U>
class PairAnimator : public Animator<U>
{
public:

	typedef U(*InterpolationFunc)(const U &, const U &, float);

private:

	U a;
	U b;
	InterpolationFunc interpolation;

	U getValue(float t) override { return interpolation(a, b, t); }

public:

	void set(U lower, U upper) { a = lower; b = upper; }
	void setLower(U lower) { a = lower; }
	void setUpper(U Upper) { b = upper; }
	void swap() { U buffer = a; a = b; b = buffer; }
	void setInterpolation(InterpolationFunc i) { interpolation = i; }

	PairAnimator() : a(), b(), interpolation(InterpolationFuncs::linear) {}
	~PairAnimator() {}
};

