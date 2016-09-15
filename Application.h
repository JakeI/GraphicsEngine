#pragma once

#include "StdAfx.h"
#include "Globals.h"
#include "RootScene.h"
#include "FpsController.h"
#include "InputState.h"
#include "Event.h"

class Application
{
private:

	std::queue<Event> eventQueue;

	struct SharedMemory {
		Application* app;
		bool running;
	};

	SharedMemory* lpSharedMemory;
	static DWORD WINAPI sceneHandler(LPVOID lpParam);

	static HDC setPixleFormatStruct(HWND hWnd);
	static void releaseWgl(HWND hWnd, HDC hDC, HGLRC hRC);

	void registerWindowClass(HINSTANCE hInstance);
	void createWindow(glm::ivec2 dim, HINSTANCE hInstance);

	static Application* getThisPtr(HWND hWnd, UINT Msg, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	HWND hWnd;
	RootScene *rootScene;

	FpsController* fpsController;

	void allocateMemory();
	void deleteMemory();
	
public:
	Application(RootScene* rootScene);
	~Application();

	void create(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
	int show();

	HWND gethWnd();

	struct WndProcData {
		bool mouseOutsideWnd;
		TRACKMOUSEEVENT tme;
		//bool mouseButtonPressed[3]; //leaving with a dragging mouse dose not yet trigger mouse_*_up events
		WndProcData();
	}wndProcData;
};

