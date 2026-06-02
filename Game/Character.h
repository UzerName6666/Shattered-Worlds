#pragma once
#include "win.h"
#include "Direct2D.h"
#include <string>
#include <vector>
#include <array>
#include <map>
#include "Engine.h"
class CharacterSprite{
	protected:
	struct DataFrames{
		int SpriteID = 0;
		int Duration = 0;
	};
	void CheckLoad();
	std::wstring CharacterName;
	int AnimFrame = 0;
	int Time = 0;
	int PassTime = 0;
	std::wstring CurrentAnimName;
	std::map<std::wstring, std::vector<DataFrames>> Anim;
	std::vector<ID2D1Bitmap*> AnimFrames;
	bool Loaded = false; // Все данные загружены корректно
	bool Usable = false; // Загружен необходимый минимум данных

	public:
	CharacterSprite(std::wstring Path, ID2D1RenderTarget* pRenderTarget);
	CharacterSprite();
	void Open(std::wstring Path, ID2D1RenderTarget* pRenderTarget);
	void DrawSprite(int SpriteID, ShatteredEngine::Vector2D Cord, ShatteredEngine::Camera& Cam);
	bool IsLoaded();
	bool IsUsable();
	bool SetAnimation(std::wstring AnimName, bool Reset);
	void PlayAnimation(int time);
	bool CheckAnim(std::wstring AnimName);
};

class PlayerCharacter: protected CharacterSprite{
	protected:
	int CordX = 0, CordY = 0;
	int OffsetX = 0, OffsetY = 0;

	int SpriteDirection = 0;
	int DirBuffer = -1;
	bool Moving = false;
	std::array<std::wstring, 12> MovementAnims;

	bool Idle = true;
	int IdleTimer = 0;
	public:
	bool HasArt = false;
	int Speed = 5;
	PlayerCharacter();
	PlayerCharacter(std::wstring Path, ID2D1RenderTarget* pRenderTarget);

	void SetMovementAnims(std::array<std::wstring, 12> NewMAnim);
	void SetMovementAnims();
	int Facing();
	void LoadSprite(std::wstring Path, ID2D1RenderTarget* pRenderTarget);
	void SetPosition(ShatteredEngine::Vector2D Cord);
	int PosX();
	int PosY();
	int TilePosX();
	int TilePosY();
	bool Correct();
	void Move(const ShatteredEngine::PlayerInput& PIn, int TileID);

	void Draw(ShatteredEngine::Vector2D Cord, ShatteredEngine::Camera& Cam);

	int XMapOffset(int MaxX, int Range);
	int YMapOffset(int MaxY, int Range);
};
