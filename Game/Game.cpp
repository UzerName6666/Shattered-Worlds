#include "Character.h"
#include "Tileset.h"
#include "Room.h"
#include "Engine.h"
Level TestMaze;
PlayerCharacter TestCharacter;

bool ShatteredEngine::GameManager::Init(){
	TileSet DebugSet(L"Gamedata\\Graphics\\Tileset\\Test", PlayerCamera.GetRenderTarget());
	if(!DebugSet.IsLoaded()){
		return false;
	}
	// Остальные не вызывают крашей и без них работает
	TileSet GrassSet(L"Gamedata\\Graphics\\Tileset\\Grass", PlayerCamera.GetRenderTarget());
	TileSet BuildSet(L"Gamedata\\Graphics\\Tileset\\Building", PlayerCamera.GetRenderTarget());
	TileSet ObjectSet(L"Gamedata\\Graphics\\Tileset\\Objects", PlayerCamera.GetRenderTarget());

	Map TestMap(Map::CreateLevelMap1());
	TestMaze = Level(TestMap, DebugSet);
	TestMaze.AddTileSet(GrassSet);
	TestMaze.AddTileSet(BuildSet);
	TestMaze.AddTileSet(ObjectSet); 
	TestMaze.SetCameraSize(PlayerCamera);
	TestCharacter.LoadSprite(L"Gamedata\\Graphics\\Character\\TestPlayer", PlayerCamera.GetRenderTarget());
	if(!TestCharacter.Correct()){
		return false;
	}
	ShatteredEngine::Vector2D StartPos(31, 12);
	TestCharacter.SetPosition(StartPos);
	
	return true;
}

bool ShatteredEngine::GameManager::Update(){
	ShatteredEngine::PlayerInput PIn= InputM.GetPlayerInput(0);
	if(PIn.C_Action1){
		int Fac = TestCharacter.Facing();
		int dir;
		if(Fac == 0){
			dir = TestMaze.TileID(TestCharacter.TilePosX(), TestCharacter.TilePosY() - 1);
		}
		else if(Fac == 1){
			dir = TestMaze.TileID(TestCharacter.TilePosX() + 1, TestCharacter.TilePosY());
		}
		else if(Fac == 2){
			dir = TestMaze.TileID(TestCharacter.TilePosX(), TestCharacter.TilePosY() + 1);
		}
		else if(Fac == 3){
			dir = TestMaze.TileID(TestCharacter.TilePosX() - 1, TestCharacter.TilePosY());
		}
		if(dir == -2 && TestCharacter.HasArt){
			TestCharacter.SetMovementAnims();
			TestCharacter.HasArt = false;
			TestCharacter.Speed = 5;
			if(Fac == 0){
				TestMaze.SetTileID(TestCharacter.TilePosX(), TestCharacter.TilePosY() - 1, -3);
			}
			else if(Fac == 1){
				TestMaze.SetTileID(TestCharacter.TilePosX() + 1, TestCharacter.TilePosY(), -3);
			}
			else if(Fac == 2){
				TestMaze.SetTileID(TestCharacter.TilePosX(), TestCharacter.TilePosY() + 1, -3);
			}
			else if(Fac == 3){
				TestMaze.SetTileID(TestCharacter.TilePosX() - 1, TestCharacter.TilePosY(), -3);
			}
			if(TestMaze.TileID(29, 15) == -3 && TestMaze.TileID(33, 15) == -3){
				TestMaze.SetTileID(30, 15, 40);
				TestMaze.SetTileID(31, 15, 32);
				TestMaze.SetTileID(32, 15, 34);
			}
		}
		else if(dir == -3 && !TestCharacter.HasArt){
			std::array<std::wstring, 12> CharAnims = {
				L"ArtUpStand", L"ArtRightStand", L"ArtDownStand", L"ArtLeftStand",
				L"ArtUpWalk", L"ArtRightWalk", L"ArtDownWalk", L"ArtLeftWalk",
				L"ArtUpStand", L"ArtRightStand", L"ArtDownStand", L"ArtLeftStand"
			};
			TestCharacter.SetMovementAnims(CharAnims);
			TestCharacter.HasArt = true;
			TestCharacter.Speed = 3;
			if(Fac == 0){
				TestMaze.SetTileID(TestCharacter.TilePosX(), TestCharacter.TilePosY() - 1, -2);
			}
			else if(Fac == 1){
				TestMaze.SetTileID(TestCharacter.TilePosX() + 1, TestCharacter.TilePosY(), -2);
			}
			else if(Fac == 2){
				TestMaze.SetTileID(TestCharacter.TilePosX(), TestCharacter.TilePosY() + 1, -2);
			}
			else if(Fac == 3){
				TestMaze.SetTileID(TestCharacter.TilePosX() - 1, TestCharacter.TilePosY(), -2);
			}
			if(TestMaze.TileID(29, 15) != -3 || TestMaze.TileID(33, 15) != -3){
				TestMaze.SetTileID(30, 15, 44);
				TestMaze.SetTileID(31, 15, 36);
				TestMaze.SetTileID(32, 15, 38);
			}
		}
	}
	Vector2D TileCord = ShatteredEngine::Vector2D(TestCharacter.TilePosX(), TestCharacter.TilePosY());
	int Tile = TestMaze.TileID(TileCord.x, TileCord.y);
	if(Tile == -4 || Tile == -5 || Tile == -6){
		MainWindow.Hide();
		int r = MessageBox(NULL, L"You win!!!", L"Game", MB_ICONINFORMATION);
		if(r == IDOK || r == IDCLOSE){
			return false;
		}
	}
	TestCharacter.Move(PIn, TestMaze.CollisionTileID(TileCord.x, TileCord.y));
	ShatteredEngine::Vector2D CameraOffset(TestCharacter.PosX() + 156, TestCharacter.PosY() + 156);
	PlayerCamera.SetPosition(CameraOffset);
	ShatteredEngine::Vector2D CharacterPos(TestCharacter.PosX(), TestCharacter.PosY() - 8);
	TestMaze.Draw(0, 65, 0, 25, 0, 0, PlayerCamera, false);
	TestCharacter.Draw(CharacterPos, PlayerCamera);
	return true;
}
