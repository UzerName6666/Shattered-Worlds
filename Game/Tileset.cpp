#include "Tileset.h"
#include <fstream>
#include "Log.h"
TileSet::TileSet(){
	
}

TileSet::TileSet(std::wstring Path, ShatteredEngine::Window& wind){
	Open(Path, wind);
}

void TileSet::Open(std::wstring Path, ShatteredEngine::Window& wind){
	Loaded = true;
	for(int i = 0; i < 17; i++){
		std::wstring tstr = Path + L"\\tile_" + std::to_wstring(i) + L".png";
		ID2D1Bitmap* Image = wind.LoadImage(tstr);
		if(!Image){
			std::wstring M = L"Tile " + std::to_wstring(i) + L" doesn't found at " + Path;
			ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Warn, M);
			Loaded = false;
		}
		Tiles[i] = Image;
	}
	if(Loaded){
		ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Message, L"Tileset from " + Path + L" loaded without problems");
	}
}

bool TileSet::IsLoaded(){
	return Loaded;
}

ID2D1Bitmap& TileSet::Tile(int i){
	return *Tiles[i];
}

void TileSet::Draw(ShatteredEngine::Camera& Cam, ShatteredEngine::Vector2D Cord, int i){
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
	Cam.Draw(Cord, Sprite);
}