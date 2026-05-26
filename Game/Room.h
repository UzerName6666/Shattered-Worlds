#pragma once
#include <vector>
#include "Tileset.h"
#include "Direct2D.h"
#include "Camera.h"

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
	bool SetCameraSize(Camera& Cam);
};

class Level{
	protected:
	
	Map LevelMap;
	std::vector<TileSet> Tiles;
	public:
	Level();
	Level(Map Collision, TileSet DebugTileSet);
	void Draw(int x1, int x2, int y1, int y2, int ofx, int ofy, Camera& Cam, bool Col = false);
	int CollisionTileID(int x, int y);
	bool SetCameraSize(Camera& Cam);
};