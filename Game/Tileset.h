#pragma once
#include <array>
#include <string>
#include "Engine.h"
class TileSet{
	private:
		std::array<ID2D1Bitmap*, 17> Tiles;
		bool Loaded = false;
	public:
		TileSet();
		TileSet(std::wstring Path, ID2D1RenderTarget* RenderTarget);
		ID2D1Bitmap& Tile(int i);
		void Open(std::wstring Path, ID2D1RenderTarget* RenderTarget);
		bool IsLoaded();	
		void Draw(ShatteredEngine::Camera& Cam, ShatteredEngine::Vector2D Cord, int i);
};