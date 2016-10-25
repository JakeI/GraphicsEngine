#include "Scene.h"
#include "Layout.h"
#include "InputState.h"
#include "RootScene.h"

#include "stlsort.h"


Scene::RelativeMouse::RelativeMouse() {
	isInside = false;
	x = 0;
	y = 0;
}

void Scene::RelativeMouse::set(bool isInside, int x, int y) {
	this->isInside = isInside;
	this->x = x;
	this->y = y;
}


Scene::Scene(Scene* parent){
	this->parent = parent;
	this->root = parent->getRoot();
	layout = nullptr;
	layer = -1;
}


Scene::~Scene()
{
	
}

void Scene::processEvent(Event* e) {
	switch (e->type) {

	case Event::EventType::KEY_DOWN:
		keyDown((char)e->a);
		break;
	case Event::EventType::KEY_UP:
		keyUp((char)e->a);
		break;
	case Event::EventType::CHAR_DOWN:
		charDown((char)e->a);
		break;
	case Event::EventType::MOUSE_MOVE:
		mouseMove(e->a, e->b);
		break;
	case Event::EventType::MOUSE_L_DOWN:
		mouseLdown(e->a, e->b);
		break;
	case Event::EventType::MOUSE_L_UP:
		mouseLup(e->a, e->b);
		break;
	case Event::EventType::MOUSE_M_DOWN:
		mouseMdown(e->a, e->b);
		break;
	case Event::EventType::MOUSE_M_UP:
		mouseMup(e->a, e->b);
		break;
	case Event::EventType::MOUSE_R_DOWN:
		mouseRdown(e->a, e->b);
		break;
	case Event::EventType::MOUSE_R_UP:
		mouseRup(e->a, e->b);
		break;
	case Event::EventType::MOUSE_WHEEL:
		mouseWheel(e->a);
		break;
	case Event::EventType::SIZE_CHANGE:
		sizeChanged(e->a, e->b);
		break;
	}
}

InputState* Scene::getInputState() {
	return root->getInputState();
}

float Scene::getTime() {
	return root->getTime();
}

RootScene* Scene::getRoot() {
	return root;
}

void Scene::processEvnetQueue(std::queue<Event>& q)
{
	while (!q.empty()) {
		Event e(q.front());
		q.pop();

		Event* eptr = &e;
		processEvent(eptr);
		for (auto child : children)
			child->processEvent(eptr);
	}
}

void Scene::getDimention(int* x, int* y, int *w, int *h) {
	*x = dimention.x;
	*y = dimention.y;
	*w = dimention.w;
	*h = dimention.h;
}

void Scene::resize(int x, int y, int w, int h) {
	dimention.x = x;
	dimention.y = y;
	dimention.w = w;
	dimention.h = h;
	if(layout != nullptr)
		layout->resize(x, y, w, h);
	//for (auto child : children)
		//child->resize(x, y, w, h);
}

void Scene::increment(float time, float deltaTime) {
	for (auto child : children)
		child->increment(time, deltaTime);
}

void Scene::render(RenderMode rm) {
	for (auto child : children)
		child->render(rm);
}

void Scene::init() {
	for (auto child : children)
		child->init();
}

void Scene::add(Scene* child) {
	children.push_back(child);
}

void Scene::remove(Scene* child) {
	children.remove(child);
}

void Scene::mouseMove(int x, int y) {
	for (auto child : children) {
		
		int relativeX = x - child->dimention.x;
		int relativeY = y - child->dimention.y;
		bool inside = relativeX < child->dimention.w && relativeX >= 0
			&& relativeY < child->dimention.h && relativeY >= 0;
		
		child->mouse.set(inside, relativeX, relativeY);
		
		if (inside) {
			child->mouseMove(relativeX, relativeY);
		}
	}
}

glm::mat4 Scene::getProjection(ProjectionType pt) {
	switch(pt){
	case STD2:
		if (dimention.w > dimention.h)
			return glm::scale(glm::mat4(1.0f), glm::vec3(
				(float)dimention.h / (float)dimention.w, 1.0f, 0.0f));
		else
			return glm::scale(glm::mat4(1.0f), glm::vec3(
				1.0f, (float)dimention.w / (float)dimention.h, 0.0f));
	}
}

glm::vec2 Scene::getMouseGl() {
	return glm::vec2((float)mouse.x / (float)dimention.w, (float)mouse.y / (float)dimention.h) * 2.0f - 1.0f;
}

bool Scene::layerLessThan(Scene* a, Scene* b) {
	if (a->layer == -1) return true;
	else return a->layer < b->layer;
}

void Scene::arangeChildren() {
	bubbleSort(children.begin(), children.end(), layerLessThan);
}