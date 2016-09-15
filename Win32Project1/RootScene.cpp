#include "RootScene.h"
#include "Layout.h"

void RootScene::processEvent(Event* e) {
	inputState->update(e);
	Scene::processEvent(e);
}

glm::ivec2 & RootScene::getPreferedDimention() {
	return preferedDim;
}

void RootScene::setPreferedDimention(const glm::ivec2 & d) {
	preferedDim = d;
}

inline InputState* RootScene::getInputState() {
	return inputState;
}

RootScene::RootScene() : Scene(NULL) {
	inputState = new InputState();
}


RootScene::~RootScene() {
	delete inputState;
}

void RootScene::allocateMemory() {
	inputState = new InputState();
}

void RootScene::deleteMemory() {
	delete inputState;
}

void RootScene::sizeChanged(int w, int h) {
	resize(0, 0, w, h);
}

void RootScene::updateLayout() {
	resize(dimention.x, dimention.y, dimention.w, dimention.h);
}