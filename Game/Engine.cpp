#include "Engine.h"
LRESULT WINAPI ShatteredEngine::GameManager::WNDProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
    if(msg == WM_INPUT){
		InputM.Update(lparam);
	}
	else if(msg == WM_CREATE){

	}
	else if(msg == WM_PAINT){
		PlayerCamera.GetRenderTarget() -> BeginDraw();
		InputM.UpdateFrame();
		Update(PlayerCamera, InputM);
		PlayerCamera.Reset();
		PlayerCamera.GetRenderTarget() -> EndDraw();
	}
	else if(msg == WM_DESTROY){
		PostQuitMessage(0);
	}
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

ShatteredEngine::GameManager::GameManager(HINSTANCE hInstance){
    pDFactory = nullptr;
    Logger::Init();
    Logger::Write(Logger::Message, L"GameManager begin loading");
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pDFactory);
    Window MainWindow(hInstance, pDFactory);
    InputM.AddKeyboard(MainWindow.GetHWND());
    PlayerCamera = Camera(MainWindow.GetRenderTarget());
    MSG msg;
    Init(PlayerCamera);
    while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		InvalidateRect(MainWindow.GetHWND(), NULL, false);
	}
}