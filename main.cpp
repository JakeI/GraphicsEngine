#include "StdAfx.h"
#include "Application.h"
#include "GeneticRootScene.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	
	Globals::init();

	GeneticRootScene grs;

	Application app(&grs);
	app.create(hInstance, hPrevInstance, pCmdLine, nCmdShow);

	return app.show();
}