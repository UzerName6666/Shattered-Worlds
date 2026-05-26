#include "win.h"
#include "Direct2D.h"
#include "Log.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"

ID2D1HwndRenderTarget* pRenderTarget = nullptr;
InputManager InputM;
Camera PlayerCamera;

LRESULT WINAPI WNDProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
	if(msg == WM_INPUT){
		InputM.Update(lparam);
	}
	else if(msg == WM_CREATE){

	}
	else if(msg == WM_PAINT){
		pRenderTarget -> BeginDraw();
		Update(PlayerCamera, InputM);
		PlayerCamera.Reset();
		pRenderTarget -> EndDraw();
	}
	else if(msg == WM_DESTROY){
		PostQuitMessage(0);
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	ID2D1Factory* pFactory = nullptr;
	Logger::Clear();
	Logger::Write(Logger::Message, L"Starting program");
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	HWND hwnd;
	MSG msg;
	WNDCLASSEXW wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = hInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WNDProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"WinMainClass";
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	RegisterClassExW(&wc);
	hwnd = CreateWindowExW(
		WS_EX_APPWINDOW,
		wc.lpszClassName,
		L"Shattered Worlds",
		WS_OVERLAPPEDWINDOW,
		screenWidth / 2 - 160, screenHeight / 2 - 160, 306, 328,
		NULL, NULL, hInstance, NULL
	);
	ShowWindow(hwnd, nCmdShow);
	
	RECT rc;
	GetClientRect(hwnd, &rc);
	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
	pFactory->CreateHwndRenderTarget(
	D2D1::RenderTargetProperties(),
	D2D1::HwndRenderTargetProperties(hwnd, size),
	&pRenderTarget
	);
	RAWINPUTDEVICE rid;
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x06;
	rid.dwFlags = 0;
	rid.hwndTarget = hwnd;
	RegisterRawInputDevices(&rid, 1, sizeof(rid));
	PlayerCamera = Camera(pRenderTarget);
	Logger::Write(Logger::Message, L"Begin Loading");
	Init(PlayerCamera);
	Logger::Write(Logger::Message, L"Loading finished");
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		InvalidateRect(hwnd, NULL, false);
	}
	Logger::Write(Logger::Message, L"Program finished");
	return msg.wParam;
}