#include "Character.h"
#include "Tileset.h"
#include "Room.h"
#include "MazeGen.h"
#include "Engine.h"
Level TestMaze;
PlayerCharacter TestCharacter;

void Init(ShatteredEngine::Camera& PlayerCamera){
	TileSet DebugSet(L"Gamedata\\Graphics\\Tileset\\Test", PlayerCamera.GetRenderTarget());
	TileSet GrassSet(L"Gamedata\\Graphics\\Tileset\\Grass", PlayerCamera.GetRenderTarget());
	Map TestMap(CreateLevelMap1());
	TestMaze = Level(TestMap, DebugSet);
	TestMaze.AddTileSet(GrassSet);
	TestMaze.SetCameraSize(PlayerCamera);
	TestCharacter.LoadSprite(L"Gamedata\\Graphics\\Character\\TestPlayer", PlayerCamera.GetRenderTarget());
	ShatteredEngine::Vector2D StartPos(31, 12);
	TestCharacter.SetPosition(StartPos);
}

void Update(ShatteredEngine::Camera& PlayerCamera, ShatteredEngine::InputManager& InputM){
	ShatteredEngine::PlayerInput PIn= InputM.GetPlayerInput(0);
	if(PIn.Action1){
		TestCharacter.Move(PIn, 0);
	}
	else{
		TestCharacter.Move(PIn, TestMaze.CollisionTileID(TestCharacter.TilePosX(), TestCharacter.TilePosY()));
	}
	ShatteredEngine::Vector2D CameraOffset(TestCharacter.PosX() + 156, TestCharacter.PosY() + 156);
	PlayerCamera.SetPosition(CameraOffset);
	if(PIn.Action1){
		ShatteredEngine::Vector2D CharacterPos(TestCharacter.PosX(), TestCharacter.PosY());
		TestMaze.Draw(0, 65, 0, 25, 0, 0, PlayerCamera, true);
		TestCharacter.Draw(CharacterPos, PlayerCamera);
	}
	else{
		ShatteredEngine::Vector2D CharacterPos(TestCharacter.PosX(), TestCharacter.PosY() - 8);
		TestMaze.Draw(0, 65, 0, 25, 0, 0, PlayerCamera, false);
		TestCharacter.Draw(CharacterPos, PlayerCamera);
	}
	
}
