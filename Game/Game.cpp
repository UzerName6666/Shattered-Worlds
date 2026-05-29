#include "Game.h"
#include "Character.h"
#include "Tileset.h"
#include "Room.h"
#include "MazeGen.h"

Level TestMaze;
PlayerCharacter TestCharacter;

void Init(Camera& PlayerCamera){
	TileSet DebugSet(L"Gamedata\\Graphics\\Tileset\\Test", PlayerCamera.GetRenderTarget());
	TileSet GrassSet(L"Gamedata\\Graphics\\Tileset\\Grass", PlayerCamera.GetRenderTarget());
	Map TestMap(CreateLevelMap1());
	TestMaze = Level(TestMap, DebugSet);
	TestMaze.AddTileSet(GrassSet);
	TestMaze.SetCameraSize(PlayerCamera);
	TestCharacter.LoadSprite(L"Gamedata\\Graphics\\Character\\TestPlayer", PlayerCamera.GetRenderTarget());
	TestCharacter.SetPosition(31, 12);
}

void Update(Camera& PlayerCamera, InputManager& InputM){
	PlayerInput PIn= InputM.GetPlayerInput(0);
	if(PIn.Action1){
		TestCharacter.Move(PIn, 0);
	}
	else{
		TestCharacter.Move(PIn, TestMaze.CollisionTileID(TestCharacter.TilePosX(), TestCharacter.TilePosY()));
	}
	PlayerCamera.SetPosition(TestCharacter.PosX() + 156, TestCharacter.PosY() + 156);
	if(PIn.Action1){
		TestMaze.Draw(0, 65, 0, 25, 0, 0, PlayerCamera, true);
		TestCharacter.Draw(TestCharacter.PosX(), TestCharacter.PosY(), PlayerCamera);
	}
	else{
		TestMaze.Draw(0, 65, 0, 25, 0, 0, PlayerCamera, false);
		TestCharacter.Draw(TestCharacter.PosX(), TestCharacter.PosY() - 8, PlayerCamera);
	}
	
}