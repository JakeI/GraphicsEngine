#pragma once

#include "StdAfx.h"
#include "Scene.h"
#include "Globals.h"
#include "Texture.h"
#include "Text.h"

class TestScene : public Scene
{
private:

	static const std::string resources[];
	static const int resourceCount;

	glm::vec4 color;
	float rotation, angular;

	Text text;

public:
	TestScene(Scene* parent, const glm::vec4 & color, float rotation, float angular);
	~TestScene();

	void render(RenderMode rm) override;
	void init() override;
	void increment(float time, float deltaTime) override;

	void charDown(char c) override;
};

