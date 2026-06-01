#pragma once
#include <vector>
#include "Tileset.h"
#include "Engine.h"
class Map{
	protected:
	std::vector<std::vector<int>> Maze;
	bool Loaded;
	public:
	bool IsLoaded();
	Map();
	Map(std::vector<std::vector<int>> map);
	void SetMap(std::vector<std::vector<int>> map);
	int GetTileID(int x, int y);
	bool SetCameraSize(ShatteredEngine::Camera& Cam);
	void SetTileID(int x, int y, int value);
};

class Level{
	protected:
	
	Map LevelMap;
	std::vector<TileSet> Tiles;
	public:
	Level();
	Level(Map Collision, TileSet DebugTileSet);
	void Draw(int x1, int x2, int y1, int y2, int ofx, int ofy, ShatteredEngine::Camera& Cam, bool Col = false);
	int CollisionTileID(int x, int y);
	int TileID(int x, int y);
	void SetTileID(int x, int y, int value);
	bool SetCameraSize(ShatteredEngine::Camera& Cam);
	void AddTileSet(TileSet NewTileset);
};