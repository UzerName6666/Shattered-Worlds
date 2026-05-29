#pragma once
#include <array>
#include <string>
#include "win.h"
#include "Direct2D.h"
#include "Camera.h"
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
		void Draw(Camera& Cam, int x, int y, int i);
};