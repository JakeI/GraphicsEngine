#pragma once
#include "Viewer2.h"
#include "ResourceManager.h"

class ViewerTest : public Viewer2
{
private:

	static const std::string resources[];
	static const int resourceCount;

	std::vector<glm::vec2> arrowPos;
	float rotation, angularSpeed;

public:
	ViewerTest(Scene* parent);
	~ViewerTest();

	void increment(float time, float deltaTime) override;
	void render(RenderMode rm) override;
	void init() override;
};

