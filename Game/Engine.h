#pragma once
#include <vector>
#include "win.h"
#include "Direct2D.h"
#include "Log.h"
namespace ShatteredEngine{

    class Vector2D{
    public:
        int x, y;
        Vector2D();
        Vector2D(int X, int Y);
        bool operator ==(Vector2D vec);
    };

    class Camera{
	protected:
	    ID2D1RenderTarget* pRenderTarget;
	    bool ChangePos;
	    Vector2D Cur;
	    Vector2D MaxSize;
	    Vector2D WindowSize;
	public:

	    bool SetPosition(Vector2D cord);
	    bool SetRoomSize(Vector2D size);

	    Camera();
	    Camera(ID2D1RenderTarget* pRenderTarget);

	    void Draw(Vector2D cord, ID2D1Bitmap* sprite);

	    bool InBound(Vector2D lu, Vector2D rd);
	    void Reset();

	    ID2D1RenderTarget* GetRenderTarget();
    };

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
    };

    class PlayerInput{
	public:
	PlayerInput();
	bool Up, Down, Right, Left, Action1;
    bool C_Up, C_Down, C_Right, C_Left, C_Action1;
    int H_Up, H_Down, H_Right, H_Left, H_Action1;
};

    class InputManager{
	private:
	    std::vector<PlayerInput> Players;
	public:
	    InputManager();
	    void Update(LPARAM lparam);
        void UpdateFrame();
	    static void AddKeyboard(HWND hwnd);
	    const PlayerInput& GetPlayerInput(int PlayerID);
    };

    class GameManager{
        public:
            static inline InputManager InputM;
            static inline Window MainWindow;
            static inline Camera PlayerCamera;
            static inline ID2D1Factory* pDFactory;
            static LRESULT WINAPI WNDProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
            GameManager(HINSTANCE hInstance);
    };
};
void Init(ShatteredEngine::Camera& PlayerCamera);
void Update(ShatteredEngine::Camera& PlayerCamera, ShatteredEngine::InputManager& InputM);