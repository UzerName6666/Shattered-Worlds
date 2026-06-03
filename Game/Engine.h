#pragma once
#include "win.h"
#include "Direct2D.h"
#include "Log.h"
#include "Vector2D.h"
#include "Camera.h"
#include "Window.h"
#include "InputManager.h"
namespace ShatteredEngine{

    class GameManager{
        public:
            static inline InputManager InputM;
            static inline Window MainWindow;
            static inline Camera PlayerCamera;
            static inline ID2D1Factory* pDFactory;
            static LRESULT WINAPI WNDProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
            GameManager(HINSTANCE hInstance);
            static ID2D1Bitmap* LoadImage(std::wstring Path, ID2D1RenderTarget* pRenderTarget);
            static bool Init();
            static bool Update();
    };

};

