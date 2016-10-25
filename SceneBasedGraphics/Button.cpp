#include "Button.h"

Button::Button(Scene* parent, const std::string & atlasPath) :
	Scene(parent),
	transform(),
	button(atlasPath)
{
	setUp();
}

Button::Button(Scene* parent, Atlas* atlasPtr) :
	Scene(parent),
	transform(),
	button(atlasPtr)
{
	setUp();
}

void Button::setUp() {
	transform.getAnimator()->setValue(Maths::Transform2());
	button.add(&transform);
}

void Button::init() {
	button.init();
}

void Button::increment(float time, float deltaTime) {
	button.increment(time, deltaTime);
}

void Button::render(RenderMode rm) {
	glViewport(dimention.x, dimention.y, dimention.w, dimention.h);
	Maths::ProjView pv;
	button.render(&pv, FULL);
}