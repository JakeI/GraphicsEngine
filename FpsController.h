#pragma once

#include "StdAfx.h"

class FpsController
{
private:

	int fps, cpf;
	int renderNextFrame;
	long lastFrameTime;

	static const float ticksPerMS;

public:

	static float clockToMSf(clock_t ticks);

	FpsController(int targetFps);
	~FpsController();

	inline bool timeIsRight() { 
		return (int)(clock()) >= renderNextFrame; 
	}

	void maybeSleep();
	void beginFrame();
};

