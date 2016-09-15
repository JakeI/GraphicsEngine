#pragma once

#include "Scene.h"
#include "InputState.h"

class RootScene : public Scene
{
private:
	InputState* inputState;

	void processEvent(Event* e) override;

	glm::ivec2 preferedDim;

protected:

	inline InputState* getInputState() override;

public:

	glm::ivec2 & getPreferedDimention();
	void setPreferedDimention(const glm::ivec2 & d);

	void allocateMemory();
	void deleteMemory();
	RootScene();
	~RootScene();

	void sizeChanged(int w, int h) override;
	void updateLayout();
};

