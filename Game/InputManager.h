#pragma once
#include <vector>
#include "win.h"

namespace ShatteredEngine{
    
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
}