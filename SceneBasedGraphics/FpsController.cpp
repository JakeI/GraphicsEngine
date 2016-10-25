#include "FpsController.h"

const float FpsController::ticksPerMS = CLOCKS_PER_SEC / 1000.0f;

float FpsController::clockToMSf(clock_t ticks) {
	return (float)ticks / ticksPerMS;
}

FpsController::FpsController(int targetFps)
{
	fps = targetFps;
	cpf = CLOCKS_PER_SEC / fps;
	renderNextFrame = 0;
	lastFrameTime = 0;
}


FpsController::~FpsController()
{
}

void FpsController::maybeSleep() {
	if ((int)(clock()) <= renderNextFrame - 3) {
		Sleep(2); // Usually causes 16ms of waittime
	}
}

void FpsController::beginFrame() {
	renderNextFrame = clock() + cpf;
	// Meassure Framerate Here
	lastFrameTime = clock();
}
