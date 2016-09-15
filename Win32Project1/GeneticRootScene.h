#pragma once

#include "StdAfx.h"
#include "RootScene.h"
#include "ResourceManager.h"
#include "TestScene.h"
#include "Layout.h"
#include "HorizontalLayout.h"
#include "VerticalLayout.h"
#include "ConstantLayout.h"
#include "InputState.h"
#include "ViewerTest.h"


class GeneticRootScene : public RootScene
{
private:

	const static std::string resources[];
	const static int resourcesCount;


	float angle; //just for testing
	GLuint vao;
	GLuint vbos[2];
	int vertexcount;

	glm::vec3 trianglePos;

	TestScene* tsRed;
	TestScene* tsBlue;
	TestScene* tsCenter;
	ViewerTest* vtMain;
	HorizontalLayout* horizontalLayout;
	VerticalLayout* verticalLayout;
	ConstantLayout* constantLayout;


public:
	GeneticRootScene();
	~GeneticRootScene();


	void render(RenderMode rm) override;

	void keyDown(char key) override;

	void init() override;

	void increment(float time, float deltaTime) override;
};

