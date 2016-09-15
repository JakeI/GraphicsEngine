#include "Transform2.h"



Transform2::Transform2() :
	translation(0.0f, 0.0f),
	scale(1.0f, 1.0f),
	rotation(0.0f)
{
}


Transform2::~Transform2()
{
}

glm::mat4 Transform2::createMatrix() {
	glm::mat4 m(1.0f);
	m = glm::translate(m, glm::vec3(translation.x, translation.y, 0.0f));
	m = glm::rotate(m, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	m = glm::scale(m, glm::vec3(scale.x, scale.y, 1.0f));
	return m;
}
