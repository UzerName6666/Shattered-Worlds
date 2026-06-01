#include "Engine.h"
ShatteredEngine::PlayerInput::PlayerInput(){
	Up = false;
	Down = false;
	Right = false;
	Left = false;
	Action1 = false;

	C_Up = false;
	C_Down = false;
	C_Right = false;
	C_Left = false;
	C_Action1 = false;

	H_Up = 0;
	H_Down = 0;
	H_Right = 0;
	H_Left = 0;
	H_Action1 = 0;
}

ShatteredEngine::InputManager::InputManager(){
	PlayerInput D;
	Players.push_back(D);
}

const ShatteredEngine::PlayerInput& ShatteredEngine::InputManager::GetPlayerInput(int PlayerID){
	return Players[0];
}

void ShatteredEngine::InputManager::UpdateFrame(){
	Players[0].C_Up = false;
	Players[0].C_Down = false;
	Players[0].C_Right = false;
	Players[0].C_Left = false;
	Players[0].C_Action1 = false;

	if(Players[0].Up && !Players[0].H_Up){
		Players[0].C_Up = true;
	}
	if(Players[0].Down && !Players[0].H_Down){
		Players[0].C_Down = true;
	}
	if(Players[0].Right && !Players[0].H_Right){
		Players[0].C_Up = true;
	}
	if(Players[0].Left && !Players[0].H_Left){
		Players[0].C_Left = true;
	}
	if(Players[0].Action1 && !Players[0].H_Action1){
		Players[0].C_Action1 = true;
	}



	if(Players[0].Up){
		Players[0].H_Up++;
	}
	else{
		Players[0].H_Up = 0;
	}
	if(Players[0].Down){
		Players[0].H_Down++;
	}
	else{
		Players[0].H_Down = 0;
	}
	if(Players[0].Right){
		Players[0].H_Right++;
	}
	else{
		Players[0].H_Right = 0;
	}
	if(Players[0].Left){
		Players[0].H_Left++;
	}
	else{
		Players[0].H_Left = 0;
	}
	if(Players[0].Action1){
		Players[0].H_Action1++;
	}
	else{
		Players[0].H_Action1 = 0;
	}
}

void ShatteredEngine::InputManager::AddKeyboard(HWND hwnd){
	RAWINPUTDEVICE rid;
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x06;
	rid.dwFlags = 0;
	rid.hwndTarget = hwnd;
	RegisterRawInputDevices(&rid, 1, sizeof(rid));
	ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Message, L"Keyboard registered");
}

void ShatteredEngine::InputManager::Update(LPARAM lparam){
	UINT dwSize = 0;
	GetRawInputData((HRAWINPUT)lparam, RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
	std::vector<BYTE> buffer(dwSize);
	if (GetRawInputData((HRAWINPUT)lparam, RID_INPUT, buffer.data(), &dwSize, sizeof(RAWINPUTHEADER)) == dwSize) {
		RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(buffer.data());
		if (raw->header.dwType == RIM_TYPEKEYBOARD){
			RAWKEYBOARD& k = raw->data.keyboard;
			if(k.MakeCode == 30){
				if(k.Flags == RI_KEY_MAKE){
					Players[0].Left = 1;
				}
				if(k.Flags == RI_KEY_BREAK){
					Players[0].Left = 0;
				}
			}
			else if(k.MakeCode == 17){
				if(k.Flags == RI_KEY_MAKE){
					Players[0].Up = 1;
				}
				if(k.Flags == RI_KEY_BREAK){
					Players[0].Up = 0;
				}
			}
			else if(k.MakeCode == 31){
				if(k.Flags == RI_KEY_MAKE){
					Players[0].Down = 1;
				}
				if(k.Flags == RI_KEY_BREAK){
					Players[0].Down = 0;
				}
			}
			else if(k.MakeCode == 32){
				if(k.Flags == RI_KEY_MAKE){
					Players[0].Right = 1;
				}
				if(k.Flags == RI_KEY_BREAK){
					Players[0].Right = 0;
				}
			}
			else if(k.MakeCode == 44){
				if(k.Flags == RI_KEY_MAKE){
					Players[0].Action1 = 1;
				}
				if(k.Flags == RI_KEY_BREAK){
					Players[0].Action1 = 0;
				}
			}
		}
	}
}