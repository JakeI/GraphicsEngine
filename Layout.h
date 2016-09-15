#pragma once

#include "StdAfx.h"

class Scene;

class Layout
{
public:

	class LayoutInfo { // only for inheritance
	public:
		virtual LayoutInfo* copy() { return nullptr; }
		virtual void del() {  }
	};

	enum ComponentType { SCENE, LAYOUT };
	struct Component {
		ComponentType type;
		void* comp;
		LayoutInfo* info;
		Component(ComponentType type, void* comp, LayoutInfo* info = nullptr);
		inline bool operator == (const Component & c) const {
			return type == c.type && comp == c.comp; //independant of weight
		}
	};

protected:

	std::list<Component> components;

public:

	struct Dimention {
		int x, y, w, h;
	}dimention;
	void getDimention(int* x, int* y, int *w, int *h);

	static void getDimention(ComponentType type, void* component, int* x, int* y, int* w, int* h);
	static void resize(ComponentType type, void* component, int x, int y, int w, int h);

	Layout();
	~Layout();
	
	void add(Scene* scene, LayoutInfo & info);
	void add(Layout* layout, LayoutInfo & info);
	void remove(Scene* scene);
	void remove(Layout* layout);

	virtual void resize(int x, int y, int w, int h);
	virtual void addLayoutInfo(LayoutInfo* info, ComponentType type) {  }
	virtual void removeLayoutInfo(LayoutInfo* info, ComponentType type) {  }
};

