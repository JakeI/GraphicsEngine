#pragma once
#include "Animator.h"

template <class U>
class ConstantAnimator : public Animator<U>
{
private:

	U value;

	U getValue(float t) override { return value; }

public:
	ConstantAnimator() : Animator(0.0f, 0.0f, ClampFuncs::one), value() {}
	ConstantAnimator(const U & v) : Animator(0.0f, 0.0f, ClampFuncs::one), value(v) {}
	~ConstantAnimator() {}
	void setValue(const U & v) { value = v; }

	void increment(float t, float dt) override {}
	U get() override { return value; }
};

typedef ConstantAnimator<float> ConstantAnimator1f;
typedef ConstantAnimator<glm::vec2> ConstantAnimator2f;
typedef ConstantAnimator<glm::vec3> ConstantAnimator3f;
typedef ConstantAnimator<glm::vec4> ConstantAnimator4f;
typedef ConstantAnimator<Maths::Transform> ConstantAnimatroTransform;
