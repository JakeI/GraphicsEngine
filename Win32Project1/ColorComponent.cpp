#include "ColorComponent.h"



ColorComponent::ColorComponent() :
	color(1.0f, 1.0f, 1.0f, 1.0f)
{
}


ColorComponent::~ColorComponent()
{
}

void ColorComponent::increment(float t, float dt) {

}

void ColorComponent::upload(Shader* shader) {
	shader->uniform("color", color);
}
