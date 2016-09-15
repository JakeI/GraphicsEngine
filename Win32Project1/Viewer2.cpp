#include "Viewer2.h"



Viewer2::Viewer2(Scene* parent) :
	Viewer(parent)
{
}


Viewer2::~Viewer2()
{
}

void Viewer2::mouseMove(int x, int y) {
	if (mouse.isInside) {
		InputState* is = getInputState();
		if (is->mouse.isRdown()) {
			camera.moveBy(glm::vec2((float)(is->mouse.dx) / (float)dimention.w,
				(float)(is->mouse.dy) / (float)dimention.h));
		}
	}
}

void Viewer2::mouseWheel(int w) {
	if (mouse.isInside) {
		InputState* is = getInputState();
		camera.scaleBy((float)is->mouse.wheel);
	}
}