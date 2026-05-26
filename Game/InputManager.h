#pragma once
#include "win.h"
#include <vector>

class PlayerInput{
	public:
	PlayerInput();
	bool Up, Down, Right, Left, Action1;

};

class InputManager{
	private:
	std::vector<PlayerInput> Players;
	public:
	InputManager();
	void Update(LPARAM lparam);
	const PlayerInput& GetPlayerInput(int PlayerID);
};