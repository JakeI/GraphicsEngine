#include "Application.h"

DWORD Application::sceneHandler(LPVOID lpParam)
{
	SharedMemory* sm = (SharedMemory*)lpParam;

	HDC hDC = Application::setPixleFormatStruct(sm->app->gethWnd());

	HGLRC hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	if (glewInit() != GLEW_OK)
		ilog->printError("Glew couldn't be initialized");

	float lastVirtualTimeMS = FpsController::clockToMSf(clock());

	sm->app->rootScene->init();

	sm->app->rootScene->processEvnetQueue(sm->app->eventQueue);
	sm->app->rootScene->increment(FpsController::clockToMSf(clock()), 0.0f);
	sm->app->rootScene->render();

	while (sm->running) {
		if (sm->app->fpsController->timeIsRight()) {
			sm->app->fpsController->beginFrame();

			SwapBuffers(hDC);

			sm->app->rootScene->processEvnetQueue(sm->app->eventQueue);

			float currenntVirtualTimeMS = FpsController::clockToMSf(clock());
			sm->app->rootScene->increment(FpsController::clockToMSf(clock()), currenntVirtualTimeMS - lastVirtualTimeMS);
			lastVirtualTimeMS = currenntVirtualTimeMS;

			sm->app->rootScene->render();
		} else {
			sm->app->fpsController->maybeSleep();
		}
	}

	releaseWgl(sm->app->gethWnd(), hDC, hRC);

	return 0;
}

HDC Application::setPixleFormatStruct(HWND hWnd) {
	
	HDC hDC = GetDC(hWnd);

	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pfd.cDepthBits = 32;
	pfd.cColorBits = 24;
	pfd.iPixelType = PFD_TYPE_RGBA;
	
	if (!SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd)) {
		ilog->printWindowsError("SetPixelFormat didn't work");
		return 0;
	}

	return hDC;
}

void Application::releaseWgl(HWND hWnd, HDC hDC, HGLRC hRC) {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	if (hWnd && hDC && !ReleaseDC(hWnd, hDC)) { // WTF sometimes the DC releaces, sometimes it dosen't, might be a mutex issue
		ilog->printWindowsError("HDC didn't release");
	}
}

void Application::registerWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex = { 
		sizeof(WNDCLASSEX), NULL, 
		WndProc, 
		NULL, NULL, hInstance,
		LoadIcon(hInstance, IDI_APPLICATION), 
		LoadCursor(hInstance, IDC_ARROW),
		(HBRUSH)CreateSolidBrush(RGB(255, 0, 0)), 
		NULL, 
		"ApplicationWindowClass", 
		NULL 
	};

	if (!RegisterClassEx(&wcex)) { 
		ilog->printWindowsError("RegisterClassEx didn't work!!");
	}
}

void Application::createWindow(glm::ivec2 dim, HINSTANCE hInstance) {
	hWnd = CreateWindow("ApplicationWindowClass", "Application Window :-)",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		(GetSystemMetrics(SM_CXSCREEN) - dim.x) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - dim.y) / 2,
		dim.x, dim.y, NULL, NULL, hInstance, this);

	if (!hWnd)
		ilog->printWindowsError("CreateWindow");
}

Application* Application::getThisPtr(HWND hWnd, UINT Msg, LPARAM lParam) {
	
	Application *app;

	if (Msg == WM_NCCREATE)
	{
		app = static_cast<Application*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

		SetLastError(0);
		if (!SetWindowLongPtr(hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(app)))
		{
			if (GetLastError() != 0)
				return FALSE;
		}
	} else {
		app = reinterpret_cast<Application*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
	}

	return app;
}

LRESULT Application::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	Application* app = Application::getThisPtr(hWnd, Msg, lParam);

	static int hight = 0; // For the convertion of mouse_y to a mathematical coordinate system

	if (app) {
		
		switch (Msg) {
		case WM_CREATE:
			app->wndProcData.tme.hwndTrack = hWnd;
			TrackMouseEvent(&app->wndProcData.tme);
			break;
		case WM_MOUSELEAVE:
			app->wndProcData.mouseOutsideWnd = true;
			break;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {
				SendMessage(hWnd, WM_QUIT, NULL, NULL);
				break;
			}

			app->eventQueue.push(Event(Event::EventType::KEY_DOWN, (int)wParam));
			break;
		case WM_KEYUP:
			app->eventQueue.push(Event(Event::EventType::KEY_UP, (int)wParam));
			break;
		case WM_CHAR:
			app->eventQueue.push(Event(Event::EventType::CHAR_DOWN, (int)wParam));
			break;
		case WM_MOUSEMOVE:
			if (app->wndProcData.mouseOutsideWnd) {
				SetCursor(LoadCursor(NULL, IDC_ARROW));
				ShowCursor(TRUE);
				app->wndProcData.mouseOutsideWnd = false;
				TrackMouseEvent(&app->wndProcData.tme);
			}

			app->eventQueue.push(Event(Event::EventType::MOUSE_MOVE, 
				LOWORD(lParam), hight - HIWORD(lParam)));
			break;
		case WM_LBUTTONDOWN:
			app->eventQueue.push(Event(Event::EventType::MOUSE_L_DOWN, 
				LOWORD(lParam), hight - HIWORD(lParam)));
			break;
		case WM_LBUTTONUP:
			app->eventQueue.push(Event(Event::EventType::MOUSE_L_UP,
				LOWORD(lParam), hight - HIWORD(lParam)));
			break;
		case WM_RBUTTONDOWN:
			app->eventQueue.push(Event(Event::EventType::MOUSE_R_DOWN,
				LOWORD(lParam), hight - HIWORD(lParam)));
			break;
		case WM_RBUTTONUP:
			app->eventQueue.push(Event(Event::EventType::MOUSE_R_UP,
				LOWORD(lParam), hight - HIWORD(lParam)));
			break;
		case WM_MBUTTONDOWN:
			app->eventQueue.push(Event(Event::EventType::MOUSE_M_DOWN,
				LOWORD(lParam), hight - HIWORD(lParam)));
			break;
		case WM_MBUTTONUP:
			app->eventQueue.push(Event(Event::EventType::MOUSE_M_UP,
				LOWORD(lParam), hight - HIWORD(lParam)));
			break;
		case WM_MOUSEWHEEL:
			app->eventQueue.push(Event(Event::EventType::MOUSE_WHEEL, GET_WHEEL_DELTA_WPARAM(wParam)));
			break;
		case WM_SIZE:
			app->eventQueue.push(Event(Event::EventType::SIZE_CHANGE, 
				LOWORD(lParam), HIWORD(lParam)));
			hight = HIWORD(lParam);
			break;

		case WM_DESTROY: case WM_QUIT: case WM_CLOSE:
			PostQuitMessage(0);
			app->lpSharedMemory->running = false;
			break;
		}
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void Application::allocateMemory() {
	fpsController = new FpsController(60);
}

void Application::deleteMemory() {
	delete fpsController;
}

Application::Application(RootScene *rootScene)
{
	this->rootScene = rootScene;
	allocateMemory();
}


Application::~Application()
{
	deleteMemory();
}

void Application::create(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	registerWindowClass(hInstance);
	glm::ivec2 prefDim = glm::ivec2(640, 480);//rootScene->getPreferedDimention();
	//glm::ivec2 dim = glm::ivec2(std::min(prefDim.x, (int)GetSystemMetrics(SM_CXSCREEN)),
	//	std::min(prefDim.x, (int)GetSystemMetrics(SM_CYSCREEN)));
	glm::ivec2 dim = prefDim;
	createWindow(dim, hInstance);
	//eventQueue.push(Event(Event::EventType::SIZE_CHANGE, dim.x, dim.y));
}

int Application::show()
{
	lpSharedMemory = (SharedMemory*)HeapAlloc(GetProcessHeap(),
		HEAP_ZERO_MEMORY, sizeof(SharedMemory));
	lpSharedMemory->app = this;
	lpSharedMemory->running = true;

	HANDLE hThread = CreateThread(NULL, 0, sceneHandler, (void*)lpSharedMemory, 0, NULL);
	if (!hThread)
		ilog->printWindowsError("CreateThread didn't work!!");

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	hWnd = NULL;

	WaitForMultipleObjects(1, &hThread, TRUE, INFINITE);

	CloseHandle(hThread);
	if (!lpSharedMemory) {
		HeapFree(GetProcessHeap(), 0, lpSharedMemory);
		lpSharedMemory = NULL;
	}

	return 0;
}

HWND Application::gethWnd() {
	if (lpSharedMemory->running)
		return hWnd;
	else
		return 0;
}

Application::WndProcData::WndProcData() {
	mouseOutsideWnd = true;

	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = NULL;
	tme.dwHoverTime = 0;
}
