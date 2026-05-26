#pragma once
#include "win.h"
#include "Direct2D.h"
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include "InputManager.h"
#include "Camera.h"

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
	std::unordered_map<std::wstring, std::vector<DataFrames>> Anim;
	std::vector<ID2D1Bitmap*> AnimFrames;
	bool Loaded = false; // Все данные загружены корректно
	bool Usable = false; // Загружен необходимый минимум данных

	public:
	CharacterSprite(std::wstring Path, ID2D1RenderTarget* pRenderTarget);
	CharacterSprite();
	void Open(std::wstring Path, ID2D1RenderTarget* pRenderTarget);
	void DrawSprite(int SpriteID, int x, int y, Camera& Cam);
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
	std::array<std::wstring, 8> MovementAnims;

	bool Idle = true;
	int IdleTimer = 0;
	public:
	int Speed = 5;
	PlayerCharacter();
	PlayerCharacter(std::wstring Path, ID2D1RenderTarget* pRenderTarget);

	void SetMovementAnims(std::array<std::wstring, 8> NewMAnim);

	void LoadSprite(std::wstring Path, ID2D1RenderTarget* pRenderTarget);
	void SetPosition(int x, int y);
	int PosX();
	int PosY();
	int TilePosX();
	int TilePosY();

	void Move(const PlayerInput& PIn, int TileID);

	void Draw(int x, int y, Camera& Cam);

	int XMapOffset(int MaxX, int Range);
	int YMapOffset(int MaxY, int Range);
};
