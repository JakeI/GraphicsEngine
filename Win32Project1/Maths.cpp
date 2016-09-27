#include "Maths.h"



Maths::Maths()
{
}


Maths::~Maths()
{
}

glm::mat4 Maths::Transform2::getMat() {
	glm::mat4 m(1.0f);
	m = glm::translate(m, glm::vec3(translation.x, translation.y, 0.0f));
	m = glm::rotate(m, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	m = glm::scale(m, glm::vec3(scale.x, scale.y, 1.0f));
	return m;
}

Maths::Transform2 Maths::Transform2::operator+(const Transform2 & t) const {
	return Transform2(translation + t.translation, scale + t.scale, rotation + t.rotation); // mayby change this so the scales have a diffrent effect
}

Maths::Transform2 Maths::Transform2::operator*(const float f) const {
	return Transform2(f*translation, f*scale, f*rotation); // maybe change this so scales have a diffrent effect
}

glm::mat4 Maths::Transform3::getMat() {
	glm::mat4 m(1.0f);
	m = glm::translate(m, translation);
	m = m * glm::toMat4(rotation);
	m = glm::scale(m, scale);
	return m;
}

Maths::Transform3 Maths::Transform3::operator+(const Maths::Transform3 & t) const {
	return Transform3(translation + t.translation, scale + t.scale, rotation * t.rotation); // maybe change this
}

Maths::Transform3 Maths::Transform3::operator*(const float f) const {
	return Transform3(f*translation, f*scale, f*rotation); // maybe change this
}