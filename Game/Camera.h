#pragma once
#include "win.h"
#include "Direct2D.h"
class Camera{
	protected:
	ID2D1RenderTarget* RT;
	bool ChangePos;
	int CurrX = 0, CurrY = 0;
	int MaxX = 0, MaxY = 0;
	int SizeX = 0, SizeY = 0;
	public:

	bool SetPosition(int x, int y);
	bool SetRoomSize(int x, int y);

	Camera();
	Camera(ID2D1RenderTarget* pRenderTarget);

	void Draw(int x, int y, ID2D1Bitmap* sprite);

	bool InBound(int x1, int x2, int y1, int y2);
	void Reset();

	ID2D1RenderTarget* GetRenderTarget();
};