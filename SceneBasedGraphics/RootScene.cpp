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

InputState* RootScene::getInputState() {
	return inputState;
}

float RootScene::getTime() {
	return time;
}

RootScene* RootScene::getRoot() {
	return this;
}

RootScene::RootScene() : Scene(this) {
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

void RootScene::increment(float time, float deltaTime) {
	this->time = time;
	Scene::increment(time, deltaTime);
}

void RootScene::init() {
	resm->init();
	Scene::init();
}