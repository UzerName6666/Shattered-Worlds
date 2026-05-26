#include "InputManager.h"

PlayerInput::PlayerInput(){
	Up = false;
	Down = false;
	Right = false;
	Left = false;
	Action1 = false;
}

InputManager::InputManager(){
	PlayerInput D;
	Players.push_back(D);
}

const PlayerInput& InputManager::GetPlayerInput(int PlayerID){
	return Players[0];
}

void InputManager::Update(LPARAM lparam){
	UINT dwSize = 0;
	GetRawInputData((HRAWINPUT)lparam, RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
	std::vector<BYTE> buffer(dwSize);
	if (GetRawInputData((HRAWINPUT)lparam, RID_INPUT, buffer.data(), &dwSize, sizeof(RAWINPUTHEADER)) == dwSize) {
		RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(buffer.data());
		if (raw->header.dwType == RIM_TYPEKEYBOARD){
			RAWKEYBOARD& k = raw->data.keyboard;
			if(k.MakeCode == 30){
				if(k.Flags == RI_KEY_MAKE){
					Players[0].Left = true;
				}
				if(k.Flags == RI_KEY_BREAK){
					Players[0].Left = false;
				}
			}
			else if(k.MakeCode == 17){
				if(k.Flags == RI_KEY_MAKE){
					Players[0].Up = true;
				}
				if(k.Flags == RI_KEY_BREAK){
					Players[0].Up = false;
				}
			}
			else if(k.MakeCode == 31){
				if(k.Flags == RI_KEY_MAKE){
					Players[0].Down = true;
				}
				if(k.Flags == RI_KEY_BREAK){
					Players[0].Down = false;
				}
			}
			else if(k.MakeCode == 32){
				if(k.Flags == RI_KEY_MAKE){
					Players[0].Right = true;
				}
				if(k.Flags == RI_KEY_BREAK){
					Players[0].Right = false;
				}
			}
			else if(k.MakeCode == 44){
				if(k.Flags == RI_KEY_MAKE){
					Players[0].Action1 = true;
				}
				if(k.Flags == RI_KEY_BREAK){
					Players[0].Action1 = false;
				}
			}
		}
	}
}