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
					Logger::Write(Logger::Warn, L"Map sise is corrupted");
					Loaded = false;
					return;
				}
			}
			Logger::Write(Logger::Message, L"Map loaded");
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

void Level::Draw(int x1, int x2, int y1, int y2, int ofx, int ofy, Camera& Cam, bool Col){
	if(Col){
		if(!LevelMap.IsLoaded()){
			return;
		}
		for(int i = x1; i <= x2; i++){
			for(int j = y1; j <= y2; j++){
				Tiles[0].Draw(Cam, i * 32 + ofx, j * 32 + ofy, LevelMap.GetTileID(i, j));
			}
		}
	}
}

int Level::CollisionTileID(int x, int y){
	return LevelMap.GetTileID(x, y);
}

bool Map::SetCameraSize(Camera& Cam){
	if(!Loaded){
		return false;
	}
	return Cam.SetRoomSize(Maze[0].size() * 32, Maze.size() * 32);
}

bool Level::SetCameraSize(Camera& Cam){
	return LevelMap.SetCameraSize(Cam);
}