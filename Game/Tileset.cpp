#include "Tileset.h"
#include <fstream>
#include "Direct2DAdd.h"
#include "Log.h"
TileSet::TileSet(){
	
}

TileSet::TileSet(std::wstring Path, ID2D1RenderTarget* RenderTarget){
	Open(Path, RenderTarget);
}

void TileSet::Open(std::wstring Path, ID2D1RenderTarget* RenderTarget){
	Loaded = true;
	for(int i = 0; i < 17; i++){
		std::wstring tstr = Path + L"\\tile_" + std::to_wstring(i) + L".png";
		ID2D1Bitmap* Image = LoadImage(tstr, RenderTarget);
		if(!Image){
			std::wstring M = L"Tile " + std::to_wstring(i) + L" doesn't found at " + Path;
			Logger::Write(Logger::Warn, M);
			Loaded = false;
		}
		Tiles[i] = Image;
	}
	if(Loaded){
		Logger::Write(Logger::Message, L"Tileset from " + Path + L" loaded without problems");
	}
}

bool TileSet::IsLoaded(){
	return Loaded;
}

ID2D1Bitmap& TileSet::Tile(int i){
	return *Tiles[i];
}

void TileSet::Draw(Camera& Cam, int x, int y, int i){
	if(!Loaded){
		return;
	}
	if(i < 0 || i > 15){
		if(i < 0){
			i = 16;
		}
		else{
			i %= 16;
		}
	}
	ID2D1Bitmap* Sprite = Tiles[i];
	D2D1_SIZE_F Size = Sprite -> GetSize();
	Cam.Draw(x, y, Sprite);
}