#include "Character.h"
#include <array>
#include <fstream>
#include "Direct2DAdd.h"
#include "Log.h"

CharacterSprite::CharacterSprite(std::wstring Path, ID2D1RenderTarget* pRenderTarget){
	Open(Path, pRenderTarget);
}
CharacterSprite::CharacterSprite(){

}
bool CharacterSprite::IsLoaded(){
	return Loaded;
}

bool CharacterSprite::IsUsable(){
	return Usable;
}

bool CharacterSprite::SetAnimation(std::wstring AnimName, bool Reset = true){
	if(Anim.find(AnimName) == Anim.end()){
		ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Warn, L"Animation with name \"" + AnimName + L"\" doesn't found inside of " + CharacterName);
		CurrentAnimName = L"Default";
		Time = 0;
		AnimFrame = 0;
		PassTime = Anim[L"Default"][0].Duration;
		return false;
	}
	CurrentAnimName = AnimName;
	if(Reset || AnimFrame >= Anim[CurrentAnimName].size() || PassTime <= 0){
		Time = 0;
		AnimFrame = 0;
	}
	PassTime = Anim[CurrentAnimName][AnimFrame].Duration;
	return true;
}

void CharacterSprite::PlayAnimation(int time){
	if(PassTime <= 0){
		return;
	}
	Time += time;
	if(Time < 0){
		while(Time < 0){
			Time += Anim[CurrentAnimName][AnimFrame].Duration;
			AnimFrame--;
			if(AnimFrame < 0){
				AnimFrame = Anim[CurrentAnimName].size() - 1;
			}
			PassTime = Anim[CurrentAnimName][AnimFrame].Duration;
		}
	}
	else{
		while (Time >= PassTime){
			Time -= Anim[CurrentAnimName][AnimFrame].Duration;
			AnimFrame++;
			if(AnimFrame >= Anim[CurrentAnimName].size()){
				AnimFrame = 0;
			}
			PassTime = Anim[CurrentAnimName][AnimFrame].Duration;
		}
		
	}
}

void CharacterSprite::Open(std::wstring Path, ID2D1RenderTarget* pRenderTarget){
	std::wifstream CharData(Path + L"\\spritesdata.txt");
	if(CharData.is_open()){
		ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Message, L"Loading character sprites from " + Path);
		Loaded = false;
		Usable = false;
		std::wstring Line;
		std::getline(CharData, CharacterName);
		std::wstring NewAnimName = L"";
		std::vector<DataFrames> NewAnimFrames;
		std::map<std::wstring, int> ListAnimFrames;
		int ID = 0;
		int LineCounter = 0;
		while (std::getline(CharData, Line)){
			LineCounter++;
			if(Line[0] == L'['){
				if(NewAnimName != L""){
					Anim[NewAnimName] = NewAnimFrames;
				}
				int i = 1;
				NewAnimName = L"";
				NewAnimFrames.clear();
				while (Line[i] != L']' && i < Line.size()){
					NewAnimName += Line[i];
					i++;
				}
				if(Line[i] != L']'){
					ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Warn, L"File had error with animation name at line " + std::to_wstring(LineCounter));
					return;
				}
			}
			else{
				std::wstring FrameName = L"";
				int i = 0;
				while (Line[i] != L' ' && i < Line.size()){
					FrameName += Line[i];
					i++;
				}
				if(i == Line.size()){
					ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Warn, L"File had error with sprite name at line " + std::to_wstring(LineCounter));
					return;
				}
				i++;
				std::map<std::wstring, int>::iterator FindFrame = ListAnimFrames.find(FrameName);
				int SpriteID;
				if(FindFrame == ListAnimFrames.end()){
					std::wstring SPath = Path + L"\\" + FrameName + L".png";
					ID2D1Bitmap* Sprite = LoadImage(SPath, pRenderTarget);
					if(Sprite == nullptr){
						ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Warn, L"File at " + SPath + L"Doesn't found");
						return;
					}
					ListAnimFrames[FrameName] = ID;
					SpriteID = ID;
					ID++;
					AnimFrames.push_back(Sprite);
				}
				else{
					SpriteID = FindFrame -> second;
				}
				if(Line[i] == L'-'){
					if(Line[i + 1] != L'1' || Line.size() != i + 2){
						ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Warn, L"File had error with sprite data at line " + std::to_wstring(LineCounter));
						return;
					}
					NewAnimFrames.push_back({SpriteID, -1});
				}
				else{
					int duration = 0;
					for(int j = i; j < Line.size(); j++){
						int numL = static_cast<int>(Line[j]) - static_cast<int>(L'0');
						if(0 > numL || numL > 9){
							ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Warn, L"File had error with sprite data at line " + std::to_wstring(LineCounter));
							return;
						}
						duration = duration * 10 + numL;
					}
					NewAnimFrames.push_back({SpriteID, duration});
				}
			}
			Anim[NewAnimName] = NewAnimFrames;
		}
	}
	AnimFrame = 0;
	CurrentAnimName = L"Default";
	ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Message, L"Checking needed animations");
	Loaded = true;
	CheckLoad();
}

void CharacterSprite::DrawSprite(int SpriteID, ShatteredEngine::Vector2D Cord, ShatteredEngine::Camera& Cam){
	if(SpriteID >= 0 && SpriteID < AnimFrames.size()){
		ID2D1Bitmap* Sprite = AnimFrames[SpriteID];
		Cam.Draw(Cord, Sprite);
	}
}

void CharacterSprite::CheckLoad(){
	Usable = false;
	std::array<std::wstring, 10> CheckList = {
		L"Icon", L"Default", 
		L"LeftStand", L"RightStand", L"DownStand", L"UpStand", 
		L"LeftWalk",  L"RightWalk",  L"DownWalk",  L"UpWalk"
	};
	for(int i = 0; i < 10; i++){
		if(Anim.find(CheckList[i]) == Anim.end() ){
			ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Error, L"Character doesn't have requered [" + CheckList[i] + L"] animation");
			return;
		}
	}
	ShatteredEngine::Logger::Write(ShatteredEngine::Logger::Message, L"Character loaded succesfully");
	Usable = true;
}

bool CharacterSprite::CheckAnim(std::wstring AnimName){
	return Anim.find(AnimName) != Anim.end();
}

PlayerCharacter::PlayerCharacter(): CharacterSprite(){

}

void PlayerCharacter::SetMovementAnims(){
	std::array<std::wstring, 12> DefaultAnims = {
		L"UpStand", L"RightStand", L"DownStand", L"LeftStand",
		L"UpWalk", L"RightWalk", L"DownWalk", L"LeftWalk",
		L"IdleUp", L"IdleRight", L"IdleDown", L"IdleLeft"
	};
	for(int i = 0; i < 12; i++){
		MovementAnims[i] = DefaultAnims[i];
	}
}

void PlayerCharacter::SetMovementAnims(std::array<std::wstring, 12> NewMAnim){
	std::array<std::wstring, 12> DefaultAnims = {
		L"UpStand", L"RightStand", L"DownStand", L"LeftStand",
		L"UpWalk", L"RightWalk", L"DownWalk", L"LeftWalk",
		L"IdleUp", L"IdleRight", L"IdleDown", L"IdleLeft"
	};
	for(int i = 0; i < 12; i++){
		if(CheckAnim(NewMAnim[i])){
			MovementAnims[i] = NewMAnim[i];
		}
		else{
			MovementAnims[i] = DefaultAnims[i];
		}
	}
}

PlayerCharacter::PlayerCharacter(std::wstring Path, ID2D1RenderTarget* pRenderTarget): CharacterSprite(Path, pRenderTarget){
	if(Usable){
		std::array<std::wstring, 12> DefaultAnims = {
			L"UpStand", L"RightStand", L"DownStand", L"LeftStand",
			L"UpWalk", L"RightWalk", L"DownWalk", L"LeftWalk",
			L"IdleUp", L"IdleRight", L"IdleDown", L"IdleLeft"
		};
		SetMovementAnims(DefaultAnims);
	}
}

void PlayerCharacter::LoadSprite(std::wstring Path, ID2D1RenderTarget* pRenderTarget){
	Open(Path, pRenderTarget);
	if(Usable){
		std::array<std::wstring, 12> DefaultAnims = {
			L"UpStand", L"RightStand", L"DownStand", L"LeftStand",
			L"UpWalk", L"RightWalk", L"DownWalk", L"LeftWalk",
			L"IdleUp", L"IdleRight", L"IdleDown", L"IdleLeft"
		};
		SetMovementAnims(DefaultAnims);
	}
}

void PlayerCharacter::Draw(ShatteredEngine::Vector2D Cord, ShatteredEngine::Camera& Cam){
	DrawSprite(Anim[CurrentAnimName][AnimFrame].SpriteID, Cord, Cam);
}

int PlayerCharacter::Facing(){
	return SpriteDirection;
}

void PlayerCharacter::SetPosition(ShatteredEngine::Vector2D Cord){
	if(Cord.x > 0){
		CordX = Cord.x;
	}
	else{
		CordX = 0;
	}
	if(Cord.y > 0){
		CordY = Cord.y;
	}
	else{
		CordY = 0;
	}
}

int PlayerCharacter::TilePosX(){
	return CordX;
}

int PlayerCharacter::TilePosY(){
	return CordY;
}

int PlayerCharacter::PosX(){
	return CordX * 32 + OffsetX + 4;
}

int PlayerCharacter::PosY(){
	return CordY * 32 + OffsetY + 4;
}
//TreeWork67
void PlayerCharacter::Move(const ShatteredEngine::PlayerInput& PIn, int TileID){
	bool Active = true;
	if(PIn.Up){
		DirBuffer = 0;
		IdleTimer = 0;
	}
	else if(PIn.Right){
		DirBuffer = 1;
		IdleTimer = 0;
	}
	else if(PIn.Down){
		DirBuffer = 2;
		IdleTimer = 0;
	}
	else if(PIn.Left){
		DirBuffer = 3;
		IdleTimer = 0;
	}
	else{
		Active = false;
	}
	if(!Moving){
		IdleTimer++;
	}
	if(IdleTimer >= 60 && !Idle){
		Idle = true;
		if(SpriteDirection == 0){
			SetAnimation(MovementAnims[8]);
		}
		else if(SpriteDirection == 1){
			SetAnimation(MovementAnims[9]);
		}
		else if(SpriteDirection == 2){
			SetAnimation(MovementAnims[10]);
		}
		else if(SpriteDirection == 3){
			SetAnimation(MovementAnims[11]);
		}
	}
	if(!Active && Idle){
		PlayAnimation(Speed);
		return;
	}
	if(!Moving){
		if(DirBuffer == SpriteDirection && !Active || DirBuffer == -1){
			if(SpriteDirection == 0){
				SetAnimation(MovementAnims[0]);
			}
			else if(SpriteDirection == 1){
				SetAnimation(MovementAnims[1]);
			}
			else if(SpriteDirection == 2){
				SetAnimation(MovementAnims[2]);
			}
			else if(SpriteDirection == 3){
				SetAnimation(MovementAnims[3]);
			}
			return;
		}
		SpriteDirection = DirBuffer;
		DirBuffer = -1;
		Idle = false;
		if(SpriteDirection == 0){
			if(TileID % 2 == 1){
				SetAnimation(MovementAnims[0]);
				return;
				
			}
			SetAnimation(MovementAnims[4], false);
		}
		else if(SpriteDirection == 1){
			if((TileID / 2) % 2 == 1){
				SetAnimation(MovementAnims[1]);
				return;
			}
			SetAnimation(MovementAnims[5], false);
		}
		else if(SpriteDirection == 2){
			if((TileID / 4) % 2 == 1){
				SetAnimation(MovementAnims[2]);
				return;
			}
			SetAnimation(MovementAnims[6], false);
		}
		else if(SpriteDirection == 3){
			if((TileID / 8) % 2 == 1){
				SetAnimation(MovementAnims[3]);
				return;
			}
			SetAnimation(MovementAnims[7], false);
		}
		Moving = true;
	}
	PlayAnimation(Speed);
	if(SpriteDirection == 0){
		OffsetY -= Speed;
		if(OffsetY < -32){
			OffsetY = -32;
		}
	}
	else if(SpriteDirection == 1){
		OffsetX += Speed;
		if(OffsetX > 32){
			OffsetX = 32;
		}
	}
	else if(SpriteDirection == 2){
		OffsetY += Speed;
		if(OffsetY > 32){
			OffsetY = 32;
		}
	}
	else if(SpriteDirection == 3){
		OffsetX -= Speed;
		if(OffsetX < -32){
			OffsetX = -32;
		}
	}

	if(OffsetX == 32 || OffsetX == -32 || OffsetY == 32 || OffsetY == -32){
		Moving = false;
	}
	if(OffsetX == 32){
		CordX++;
		OffsetX = 0;
	}
	else if(OffsetX == -32){
		CordX--;
		OffsetX = 0;
	}
	else if(OffsetY == 32){
		CordY++;
		OffsetY = 0;
	}
	else if(OffsetY == -32){
		CordY--;
		OffsetY = 0;
	}
}

int PlayerCharacter::XMapOffset(int MaxX, int Range){
	int x = 4 + CordX * 32 + OffsetX;
	if((Range - 1) * 32 <= x){
		x -= (MaxX - Range) * 32;
		if(x < 0){
			return -OffsetX;
		}	
	}
	return 0;
}

int PlayerCharacter::YMapOffset(int MaxY, int Range){
	int y = 4 + CordY * 32 + OffsetY;
	if((Range - 1) * 32 <= y){
		y -= (MaxY - Range) * 32;
		if(y < 0){
			return -OffsetY;
		}	
	}
	return 0;
}