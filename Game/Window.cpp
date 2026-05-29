#include "Engine.h"

ShatteredEngine::Window::Window(){
    pRenderTarget = nullptr;
}

bool ShatteredEngine::Window::Init(HINSTANCE hInstance, ID2D1Factory* pFactory){
    if(pRenderTarget){
        Logger::Write(Logger::Error, L"ReInit of window detected");
        return false;
    }
    if(!pFactory){
        Logger::Write(Logger::Error, L"Failed to create window, pFactory = nullptr");
        return false;
    }
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
	wc.lpfnWndProc = GameManager::WNDProc;
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
    RECT rc;
	GetClientRect(hwnd, &rc);
	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
	pFactory->CreateHwndRenderTarget(
	D2D1::RenderTargetProperties(),
	D2D1::HwndRenderTargetProperties(hwnd, size),
	&pRenderTarget
	);
    ShowWindow(hwnd, 10);
    Logger::Write(Logger::Message, L"Window created");
    return true;
}

ShatteredEngine::Window::Window(HINSTANCE hInstance, ID2D1Factory* pFactory){
    pRenderTarget = nullptr;
    Init(hInstance, pFactory);
}

HWND ShatteredEngine::Window::GetHWND(){
    return hwnd;
}

ID2D1HwndRenderTarget* ShatteredEngine::Window::GetRenderTarget(){
    return pRenderTarget;
}

bool ShatteredEngine::Window::Loaded(){
    return pRenderTarget;
}

