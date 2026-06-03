#include "win.h"
#include "Main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	ShatteredEngine::GameManager::pDFactory = nullptr;
	ShatteredEngine::GameManager::InputM;
	ShatteredEngine::GameManager::MainWindow;
	ShatteredEngine::GameManager::PlayerCamera;
	ShatteredEngine::GameManager::GD;
	ShatteredEngine::GameManager GM(hInstance);
}