#pragma once
#include "Engine.h"
#include "GameData.h"
namespace ShatteredEngine{
    class GameManager{
        public:
            static inline GameData GD;
            static inline InputManager InputM;
            static inline Window MainWindow;
            static inline Camera PlayerCamera;
            static inline ID2D1Factory* pDFactory;
            static LRESULT WINAPI WNDProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
            GameManager(HINSTANCE hInstance);
            static bool Init();
            static bool Update();
    };
};