#include "Layout.h"
#include "Scene.h"


Layout::Component::Component(ComponentType type, void* comp, LayoutInfo* info) {
	this->type = type;
	this->comp = comp;
	this->info = info;
}

void Layout::getDimention(int* x, int* y, int *w, int *h) {
	*x = dimention.x;
	*y = dimention.y;
	*w = dimention.w;
	*h = dimention.h;
}

void Layout::getDimention(ComponentType type, void* component, int* x, int* y, int* w, int* h) {
	switch (type) {
	case SCENE:
		((Scene*)component)->getDimention(x, y, w, h);
		break;
	case LAYOUT:
		((Layout*)component)->getDimention(x, y, w, h);
		break;
	}
}

void Layout::resize(ComponentType type, void* component, int x, int y, int w, int h) {
	switch (type) {
	case SCENE:
		((Scene*)component)->resize(x, y, w, h);
		break;
	case LAYOUT:
		((Layout*)component)->resize(x, y, w, h);
		break;
	}
}

Layout::Layout()
{
}


Layout::~Layout()
{
}

void Layout::add(Scene* scene, LayoutInfo & info) {
	LayoutInfo* i = info.copy();

	components.push_back(Component(ComponentType::SCENE, (void*)scene, i));
	addLayoutInfo(i, ComponentType::SCENE);
}

void Layout::add(Layout* layout, LayoutInfo & info) {
	LayoutInfo* i = info.copy();

	components.push_back(Component(ComponentType::LAYOUT, (void*)layout, i));
	addLayoutInfo(i, ComponentType::LAYOUT);
}

void Layout::remove(Scene* scene) {
	std::list<Component>::iterator it = std::find(components.begin(), components.end(),
		Component(ComponentType::SCENE, (void*)scene));
	if (it == components.end())
		return;
	removeLayoutInfo(it->info, ComponentType::SCENE);
	it->info->del();
	components.erase(it);
}

void Layout::remove(Layout* layout) {
	std::list<Component>::iterator it = std::find(components.begin(), components.end(),
		Component(ComponentType::LAYOUT, (void*)layout));
	if (it == components.end())
		return;
	removeLayoutInfo(it->info, ComponentType::LAYOUT);
	it->info->del();
	components.erase(it);
}

void Layout::resize(int x, int y, int w, int h) {
	dimention.x = x;
	dimention.y = y;
	dimention.w = w;
	dimention.h = h;
}
