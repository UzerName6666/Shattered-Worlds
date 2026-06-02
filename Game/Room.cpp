#include "Room.h"
#include "Log.h"
int Map::GetTileID(int x, int y){
	if(x < 0 || y < 0 || y >= Maze.size() || x >= Maze[0].size()){
		return -1;
	}
	return Maze[y][x];
}

Map::Map(){
	Loaded = false;
};

Map::Map(std::vector<std::vector<int>> map){
	SetMap(map);
}

void Map::SetMap(std::vector<std::vector<int>> map){
	Maze = map;
	if(Maze.size() > 0){
		if(Maze[0].size() > 0){
			int T = Maze[0].size();
			for(int i = 1; i < Maze.size(); i++){
				if(Maze[i].size() != T){
					ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Warn, L"Map sise is corrupted");
					Loaded = false;
					return;
				}
			}
			ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Message, L"Map loaded");
			Loaded = true;
		}
	}
}

bool Map::IsLoaded(){
	return Loaded;
}

Level::Level(){
	
}

Level::Level(Map Collision, TileSet DebugTileSet){
	LevelMap = Collision;
	Tiles.push_back(DebugTileSet);
}

void Level::AddTileSet(TileSet NewTileset){
	if(NewTileset.IsLoaded()){
		Tiles.push_back(NewTileset);
	}
	else{
		ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Error, L"Trying load a broken tileset");
	}
	
}

int SpecialTileID(int TileID){
	if(TileID == -1){
		return -1;
	}
	if(TileID == -2){
		return 49;
	}
	if(TileID == -3){
		return 48;
	}
	if(TileID == -4){
		return 40;
	}
	if(TileID == -5){
		return 32;
	}
	if(TileID == -6){
		return 34;
	}
	return -1;
}

void Level::Draw(int x1, int x2, int y1, int y2, int ofx, int ofy, ShatteredEngine::Camera& Cam, bool Col){
	if(!LevelMap.IsLoaded()){
		return;
	}
	if(Col){
		for(int i = x1; i <= x2; i++){
			for(int j = y1; j <= y2; j++){
				ShatteredEngine::Vector2D PCord(i * 32 + ofx, j * 32 + ofy);
				Tiles[0].Draw(Cam, PCord, LevelMap.GetTileID(i, j));
			}
		}
	}
	else{
		for(int i = x1; i <= x2; i++){
			for(int j = y1; j <= y2; j++){
				int TileID = LevelMap.GetTileID(i, j);
				if(TileID < 0){
					TileID = SpecialTileID(TileID);
				}
				ShatteredEngine::Vector2D PCord(i * 32 + ofx, j * 32 + ofy);
				if(TileID / 16 >= Tiles.size()){
					Tiles[0].Draw(Cam, PCord, TileID % 16);
				}
				else{
					Tiles[TileID / 16].Draw(Cam, PCord, TileID % 16);
				}
			}
		}
	}
}

int Level::CollisionTileID(int x, int y){
	int Tile = LevelMap.GetTileID(x, y);
	if(Tile >= 0){
		return Tile % 16;
	}
	else{
		return SpecialTileID(Tile);
	}
}

int Level::TileID(int x, int y){
	return LevelMap.GetTileID(x, y);;
}

void Level::SetTileID(int x, int y, int value){
	LevelMap.SetTileID(x, y, value);
}

void Map::SetTileID(int x, int y, int value){
	Maze[y][x] = value;
}

bool Map::SetCameraSize(ShatteredEngine::Camera& Cam){
	if(!Loaded){
		return false;
	}
	ShatteredEngine::Vector2D Cord(Maze[0].size() * 32, Maze.size() * 32);
	return Cam.SetRoomSize(Cord);
}

bool Level::SetCameraSize(ShatteredEngine::Camera& Cam){
	return LevelMap.SetCameraSize(Cam);
}