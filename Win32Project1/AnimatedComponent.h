#pragma once
#include "EntityComponent.h"
#include "Animator.h"
#include "Maths.h"
#include "ConstantAnimator.h"
#include "PairAnimator.h"

template<const EntityComponent::Type T, class Animator_t>
class AnimatedComponent : public EntityComponent
{
private:

	Animator_t animator;

public:

	AnimatedComponent() : animator() {}
	~AnimatedComponent() { }

	void increment(float t, float dt) override { animator.increment(t, dt); }

	EntityComponent::Type getType() const override { return T; }
	void get(void* buffer) override {
		animator.getToBuffer(buffer); }

	Animator_t* getAnimator() { return &animator; }
};

// Transform2
typedef AnimatedComponent<EntityComponent::Type::TRANSFORM2, ConstantAnimator<Maths::Transform2>> ConstTransform2Comp;
typedef AnimatedComponent<EntityComponent::Type::TRANSFORM2, PairAnimator<Maths::Transform2>> PairTransform2Comp;

// transform3
typedef AnimatedComponent<EntityComponent::Type::TRANSFORM3, ConstantAnimator<Maths::Transform3>> ConstTransform3Comp;
typedef AnimatedComponent<EntityComponent::Type::TRANSFORM3, PairAnimator<Maths::Transform3>> PairTransform3Comp;

// Color
typedef AnimatedComponent<EntityComponent::Type::COLOR, ConstantAnimator<glm::vec4>> ConstColorComp;
typedef AnimatedComponent<EntityComponent::Type::COLOR, PairAnimator<glm::vec4>> PairColorComp;

// Text Type Scalar
typedef AnimatedComponent<EntityComponent::Type::TYPE_SCALAR, ConstantAnimator<glm::vec4>> ConstTextTypeScalarComp;

// Text Body Color
typedef AnimatedComponent<EntityComponent::Type::TYPE_SCALAR, ConstantAnimator<glm::vec4>> ConstTextBodyColorComp;

// Text Outline Color
typedef AnimatedComponent<EntityComponent::Type::TYPE_SCALAR, ConstantAnimator<glm::vec4>> ConstTextOutlineColorComp;

// Text Distnace Edges
typedef AnimatedComponent<EntityComponent::Type::TYPE_SCALAR, ConstantAnimator<glm::vec4>> ConstTextDistanceEdgesComp;

// Text Shaddow Color
typedef AnimatedComponent<EntityComponent::Type::TYPE_SCALAR, ConstantAnimator<glm::vec4>> ConstTextShaddowColorComp;

// Text Shaddow Param
typedef AnimatedComponent<EntityComponent::Type::TYPE_SCALAR, ConstantAnimator<glm::vec4>> ConstTextShaddowParamComp;

// Text Background Color
typedef AnimatedComponent<EntityComponent::Type::TYPE_SCALAR, ConstantAnimator<glm::vec4>> ConstTextBackgroundColorComp;