#pragma once

#include "Scene.h"
#include "ButtonEntity.h"

class Button : public Scene {
private:

	ConstTransform2Comp transform;
	ButtonEntity button;

	void setUp();

public:
	Button(Scene* parent, const std::string & atlasPath);
	Button(Scene* parent, Atlas* atlasPtr);

	void init() override;
	void increment(float time, float deltaTime) override;
	void render(RenderMode rm = RenderMode::ALL) override;
};