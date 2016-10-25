#pragma once

#include "Scene.h"
#include "InputState.h"

class RootScene : public Scene
{
private:
	InputState* inputState;
	float time;

	void processEvent(Event* e) override;

	glm::ivec2 preferedDim;

public:

	InputState* getInputState() override;
	float getTime() override;
	RootScene* getRoot() override;

	glm::ivec2 & getPreferedDimention();
	void setPreferedDimention(const glm::ivec2 & d);

	void allocateMemory();
	void deleteMemory();
	RootScene();
	~RootScene();

	virtual void increment(float time, float deltaTime) override;
	virtual void init() override;

	void sizeChanged(int w, int h) override;
	void updateLayout();
};

