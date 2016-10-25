#pragma once

#include "Viewer.h"
#include "Camera2.h"

class Viewer2 : public Viewer
{
protected:

	Camera2 camera;

public:
	Viewer2(Scene* parent);
	~Viewer2();

	virtual void mouseMove(int x, int y) override;
	virtual void mouseWheel(int w) override;
};

