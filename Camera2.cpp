#include "Camera2.h"



Camera2::Camera2() :
	center(0.0f, 0.0f, 3.0f, -3.0f, -3.0f, 3.0f),//center(0.0f, 0.0f, 100.0f, -100.0f, -100.0f, 100.0f),
	dragSpeed(5.0f),
	scale(0.2f, 5.0f, 1.0f),
	scaleSpeed(0.001f)
{
}


Camera2::~Camera2()
{
}

void Camera2::moveBy(glm::vec2 & delta) {
	center.x = fmin(center.r, fmax(center.l, center.x + dragSpeed*scale.current*delta.x));
	center.y = fmin(center.t, fmax(center.b, center.y + dragSpeed*scale.current*delta.y));
}

void Camera2::scaleBy(float delta) {
	scale.current = fmin(scale.max, fmax(scale.min, scale.current + scaleSpeed*delta));
}

glm::mat4 Camera2::getView() {
	glm::mat4 v(1.0f);
	v = glm::translate(v, glm::vec3(center.x, center.y, 0.0f));
	v = glm::scale(v, glm::vec3(scale.current, scale.current, 0.0f));
	return v;
}
