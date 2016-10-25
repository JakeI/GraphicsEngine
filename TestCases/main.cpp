#include <StdAfx.h>
#include <Application.h>
#include "GeneticRootScene.h"

#include "ResourceManager.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	
	// Set Environment variables
	resm->resPath = "../SceneBasedGraphics/";
	resm->assPath = "";

	Globals::init();

	GeneticRootScene grs;

	Application app(&grs);
	app.create(hInstance, hPrevInstance, pCmdLine, nCmdShow);

	return app.show();
}