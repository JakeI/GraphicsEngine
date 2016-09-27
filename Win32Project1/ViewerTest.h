#pragma once
#include "Viewer2.h"
#include "ResourceManager.h"
#include "ModelEnity.h"
#include "Text.h"

class ViewerTest : public Viewer2
{
private:

	//static const std::string resources[];
	//static const int resourceCount;

	/*std::vector<glm::vec2> arrowPos;
	float rotation, angularSpeed;*/

	struct ConstModelEntity {
		ConstColorComp color;
		ConstTransform2Comp transform;
		ModelEntity entity;
		ConstModelEntity(const std::string & path) : entity(path) {}
	} background, arrow;

	struct PairTransformedModelEntity {
		ConstColorComp color;
		PairTransform2Comp transform;
		ModelEntity entity;
		PairTransformedModelEntity(const std::string & path) : entity(path) {}
	} arrow_m;

	struct ConstTextEntity {
		ConstTransform2Comp transform;
		Text text;
	} text;

public:
	ViewerTest(Scene* parent);
	~ViewerTest();

	void increment(float time, float deltaTime) override;
	void render(RenderMode rm) override;
	void init() override;

	void charDown(char c) override;
};

