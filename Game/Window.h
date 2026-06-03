#pragma once
#include "win.h"
#include "Direct2D.h"
#include <string>
namespace ShatteredEngine{
    class Window{
        protected:
            HWND hwnd;
            ID2D1HwndRenderTarget* pRenderTarget;
        public:
            ID2D1Bitmap* LoadImage(std::wstring Path);
            Window();
            Window(HINSTANCE hInstance, ID2D1Factory* pFactory);
            bool Init(HINSTANCE hInstance, ID2D1Factory* pFactory);
            HWND GetHWND();
            ID2D1HwndRenderTarget* GetRenderTarget();
            bool Loaded();
            void Show();
            void Hide();
    };
}