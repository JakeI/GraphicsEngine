#pragma once

#include "StdAfx.h"
#include "InputState.h"
#include "Event.h"

class Layout;

#define LAYER_BOTTOM	-1

class Scene
{
private:

	Scene* parent;
	int layer;

	std::list<Scene*> children;
	Layout* layout;
	

protected:

	virtual void processEvent(Event* e);

	inline virtual InputState* getInputState();

public:

	struct Dimention {
		int x, y, w, h;
	}dimention;
	void getDimention(int* x, int* y, int *w, int *h);
	
	void setLayoutPtr(Layout* layout) { this->layout = layout; }
	void setLayer(int layer) { this->layer = layer; }

	void arangeChildren();
	static inline bool layerLessThan(Scene* a, Scene* b);

	struct RelativeMouse {
		bool isInside;
		int x, y;
		RelativeMouse();
		void set(bool isInside, int x, int y);
	} mouse;

	Scene(Scene* parent);
	~Scene();

	void processEvnetQueue(std::queue<Event>& q);

	virtual void keyDown(char key) {  }
	virtual void keyUp(char key) {  }
	virtual void charDown(char c) {  }
	
	virtual void mouseMove(int x, int y);

	virtual void mouseRdown(int x, int y) {  }
	virtual void mouseRup(int x, int y) {  }
	virtual void mouseMdown(int x, int y) {  }
	virtual void mouseMup(int x, int y) {  }
	virtual void mouseLdown(int x, int y) {  }
	virtual void mouseLup(int x, int y) {  }

	virtual void mouseWheel(int w) {  }

	virtual void sizeChanged(int w, int h) {  }

	virtual void resize(int x, int y, int w, int h);
	virtual void increment(float time, float deltaTime);
	enum RenderMode{ ALL, OUTPUT, MOUSEPICKING };
	virtual void render(RenderMode rm = RenderMode::ALL);

	virtual void init();

	void add(Scene* child);
	void remove(Scene* child);

	glm::vec2 getMouseGl();

	enum ProjectionType { STD2 };
	glm::mat4 getProjection(ProjectionType pt = STD2);
};

