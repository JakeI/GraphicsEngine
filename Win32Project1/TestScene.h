#pragma once

#include "StdAfx.h"
#include "Scene.h"
#include "Globals.h"
#include "Text.h"
#include "ModelEnity.h"

class TestScene : public Scene
{
private:

	/*static const std::string resources[];
	static const int resourceCount;*/

	//glm::vec4 color;
	//float rotation, angular;

	struct ConstModelEntity {
		ConstColorComp color;
		ConstTransform2Comp transform;
		ModelEntity entity;
		ConstModelEntity(const std::string & path) : entity(path) {}
	} mona;

	struct ConstTransformModelEntity {
		ConstTransform2Comp transform;
		ModelEntity entity;
		ConstTransformModelEntity(const std::string & path) : entity(path) {}
	} ;

	struct PartAnimatedModelEntity {
		ConstTransform2Comp transform;
		PairColorComp color;
		ModelEntity entity;
		PartAnimatedModelEntity(const std::string & path) : entity(path) {}
	} background;

	//Text text;

public:
	TestScene(Scene* parent, const glm::vec4 & color, float rotation, float angular);
	~TestScene();

	void render(RenderMode rm) override;
	void init() override;
	void increment(float time, float deltaTime) override;

	void charDown(char c) override;

	void mouseLdown(int x, int y) override;
};

