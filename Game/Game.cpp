#include "Character.h"
#include "Tileset.h"
#include "Room.h"
#include "Main.h"

bool ShatteredEngine::GameManager::Init(){
	TileSet DebugSet(L"Gamedata\\Graphics\\Tileset\\Test", MainWindow);
	if(!DebugSet.IsLoaded()){
		return false;
	}
	// Остальные не вызывают крашей и без них работает
	TileSet GrassSet(L"Gamedata\\Graphics\\Tileset\\Grass", MainWindow);
	TileSet BuildSet(L"Gamedata\\Graphics\\Tileset\\Building", MainWindow);
	TileSet ObjectSet(L"Gamedata\\Graphics\\Tileset\\Objects", MainWindow);

	Map TestMap(Map::CreateLevelMap1());
	GD.TestMaze = Level(TestMap, DebugSet);
	GD.TestMaze.AddTileSet(GrassSet);
	GD.TestMaze.AddTileSet(BuildSet);
	GD.TestMaze.AddTileSet(ObjectSet); 
	GD.TestMaze.SetCameraSize(PlayerCamera);
	GD.TestCharacter.LoadSprite(L"Gamedata\\Graphics\\Character\\TestPlayer", MainWindow);
	if(!GD.TestCharacter.Correct()){
		return false;
	}
	ShatteredEngine::Vector2D StartPos(31, 12);
	GD.TestCharacter.SetPosition(StartPos);
	
	return true;
}

bool ShatteredEngine::GameManager::Update(){
	ShatteredEngine::PlayerInput PIn= InputM.GetPlayerInput(0);
	if(PIn.C_Action1){
		int Fac = GD.TestCharacter.Facing();
		int dir;
		if(Fac == 0){
			dir = GD.TestMaze.TileID(GD.TestCharacter.TilePosX(), GD.TestCharacter.TilePosY() - 1);
		}
		else if(Fac == 1){
			dir = GD.TestMaze.TileID(GD.TestCharacter.TilePosX() + 1, GD.TestCharacter.TilePosY());
		}
		else if(Fac == 2){
			dir = GD.TestMaze.TileID(GD.TestCharacter.TilePosX(), GD.TestCharacter.TilePosY() + 1);
		}
		else if(Fac == 3){
			dir = GD.TestMaze.TileID(GD.TestCharacter.TilePosX() - 1, GD.TestCharacter.TilePosY());
		}
		if(dir == -2 && GD.TestCharacter.HasArt){
			GD.TestCharacter.SetMovementAnims();
			GD.TestCharacter.HasArt = false;
			GD.TestCharacter.Speed = 5;
			if(Fac == 0){
				GD.TestMaze.SetTileID(GD.TestCharacter.TilePosX(), GD.TestCharacter.TilePosY() - 1, -3);
			}
			else if(Fac == 1){
				GD.TestMaze.SetTileID(GD.TestCharacter.TilePosX() + 1, GD.TestCharacter.TilePosY(), -3);
			}
			else if(Fac == 2){
				GD.TestMaze.SetTileID(GD.TestCharacter.TilePosX(), GD.TestCharacter.TilePosY() + 1, -3);
			}
			else if(Fac == 3){
				GD.TestMaze.SetTileID(GD.TestCharacter.TilePosX() - 1, GD.TestCharacter.TilePosY(), -3);
			}
			if(GD.TestMaze.TileID(29, 15) == -3 && GD.TestMaze.TileID(33, 15) == -3){
				GD.TestMaze.SetTileID(30, 15, 40);
				GD.TestMaze.SetTileID(31, 15, 32);
				GD.TestMaze.SetTileID(32, 15, 34);
			}
		}
		else if(dir == -3 && !GD.TestCharacter.HasArt){
			std::array<std::wstring, 12> CharAnims = {
				L"ArtUpStand", L"ArtRightStand", L"ArtDownStand", L"ArtLeftStand",
				L"ArtUpWalk", L"ArtRightWalk", L"ArtDownWalk", L"ArtLeftWalk",
				L"ArtUpStand", L"ArtRightStand", L"ArtDownStand", L"ArtLeftStand"
			};
			GD.TestCharacter.SetMovementAnims(CharAnims);
			GD.TestCharacter.HasArt = true;
			GD.TestCharacter.Speed = 3;
			if(Fac == 0){
				GD.TestMaze.SetTileID(GD.TestCharacter.TilePosX(), GD.TestCharacter.TilePosY() - 1, -2);
			}
			else if(Fac == 1){
				GD.TestMaze.SetTileID(GD.TestCharacter.TilePosX() + 1, GD.TestCharacter.TilePosY(), -2);
			}
			else if(Fac == 2){
				GD.TestMaze.SetTileID(GD.TestCharacter.TilePosX(), GD.TestCharacter.TilePosY() + 1, -2);
			}
			else if(Fac == 3){
				GD.TestMaze.SetTileID(GD.TestCharacter.TilePosX() - 1, GD.TestCharacter.TilePosY(), -2);
			}
			if(GD.TestMaze.TileID(29, 15) != -3 || GD.TestMaze.TileID(33, 15) != -3){
				GD.TestMaze.SetTileID(30, 15, 44);
				GD.TestMaze.SetTileID(31, 15, 36);
				GD.TestMaze.SetTileID(32, 15, 38);
			}
		}
	}
	Vector2D TileCord = ShatteredEngine::Vector2D(GD.TestCharacter.TilePosX(), GD.TestCharacter.TilePosY());
	int Tile = GD.TestMaze.TileID(TileCord.x, TileCord.y);
	if(Tile == -4 || Tile == -5 || Tile == -6){
		MainWindow.Hide();
		int r = MessageBox(NULL, L"You win!!!", L"Game", MB_ICONINFORMATION);
		if(r == IDOK || r == IDCLOSE){
			return false;
		}
	}
	GD.TestCharacter.Move(PIn, GD.TestMaze.CollisionTileID(TileCord.x, TileCord.y));
	ShatteredEngine::Vector2D CameraOffset(GD.TestCharacter.PosX() + 156, GD.TestCharacter.PosY() + 156);
	PlayerCamera.SetPosition(CameraOffset);
	ShatteredEngine::Vector2D CharacterPos(GD.TestCharacter.PosX(), GD.TestCharacter.PosY() - 8);
	GD.TestMaze.Draw(0, 65, 0, 25, 0, 0, PlayerCamera, false);
	GD.TestCharacter.Draw(CharacterPos, PlayerCamera);
	return true;
}
