#pragma once
#include "Direct2D.h"
namespace ShatteredEngine{
    class Window{
        protected:
            HWND hwnd;
            ID2D1HwndRenderTarget* pRenderTarget;
        public:
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