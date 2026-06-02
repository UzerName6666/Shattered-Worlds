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
	if(0 > PlayerID || PlayerID >= Players.size()){
		return Players[0];
	}
	return Players[PlayerID];
}

void ShatteredEngine::InputManager::UpdateFrame(){
	for(int i = 0; i < Players.size(); i++){
		Players[i].C_Up = false;
		Players[i].C_Down = false;
		Players[i].C_Right = false;
		Players[i].C_Left = false;
		Players[i].C_Action1 = false;

		if(Players[i].Up && !Players[i].H_Up){
			Players[i].C_Up = true;
		}
		if(Players[i].Down && !Players[i].H_Down){
			Players[i].C_Down = true;
		}
		if(Players[i].Right && !Players[i].H_Right){
			Players[i].C_Up = true;
		}
		if(Players[i].Left && !Players[i].H_Left){
			Players[i].C_Left = true;
		}
		if(Players[i].Action1 && !Players[i].H_Action1){
			Players[i].C_Action1 = true;
		}

		if(Players[i].Up){
			Players[i].H_Up++;
		}
		else{
			Players[i].H_Up = 0;
		}
		if(Players[i].Down){
			Players[i].H_Down++;
		}
		else{
			Players[i].H_Down = 0;
		}
		if(Players[i].Right){
			Players[i].H_Right++;
		}
		else{
			Players[i].H_Right = 0;
		}
		if(Players[i].Left){
			Players[i].H_Left++;
		}
		else{
			Players[i].H_Left = 0;
		}
		if(Players[i].Action1){
			Players[i].H_Action1++;
		}
		else{
			Players[i].H_Action1 = 0;
		}
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
			// Player 1
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