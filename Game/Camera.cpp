#include "Camera.h"

Camera::Camera(){
	RT = nullptr;
}

Camera::Camera(ID2D1RenderTarget* pRenderTarget){
	RT = pRenderTarget;
	SizeX = pRenderTarget -> GetSize().width;
	SizeY = pRenderTarget -> GetSize().height;
	MaxX = SizeX;
	MaxY = SizeY;
	CurrX = 0;
	CurrY = 0;
	ChangePos = true;
}

void Camera::Reset(){
	ChangePos = true;
}

void Camera::Draw(int x, int y, ID2D1Bitmap* sprite){
	if(RT && sprite){
		if(InBound(x, x + sprite -> GetSize().width, y, y + sprite -> GetSize().height)){
			RT -> DrawBitmap(sprite, D2D1::RectF(x - CurrX, y - CurrY, x - CurrX + sprite -> GetSize().width, y - CurrY + sprite -> GetSize().height));
		}
		ChangePos = false;
	}
}

bool Camera::InBound(int x1, int x2, int y1, int y2){
	if(!RT){
		return false;
	}
	if(x2 < x1 || y2 < y1){
		return false;
	}
	if(x1 > CurrX + SizeX || x2 < CurrX){
		return false;
	}
	if(y1 > CurrY + SizeY || y2 < CurrY){
		return false;
	}
	return true;
}

bool Camera::SetPosition(int x, int y){
	if(!RT){
		return false;
	}
	if(!ChangePos){
		return false;
	}
	CurrX = x - SizeX;
	CurrY = y - SizeY;
	if(CurrX < 0){
		CurrX = 0;
	}
	if(CurrX > MaxX - SizeX){
		CurrX = MaxX - SizeX;
	}
	if(CurrY < 0){
		CurrY = 0;
	}
	if(CurrY > MaxY - SizeY){
		CurrY = MaxY - SizeY;
	}
	return true;
}

bool Camera::SetRoomSize(int x, int y){
	if(!ChangePos || !RT){
		return false;
	}
	MaxX = x;
	MaxY = y;
	if(MaxX < SizeX){
		MaxX = SizeX;
	}
	if(MaxY < SizeY){
		MaxY = SizeY;
	}
	return true;
}

ID2D1RenderTarget* Camera::GetRenderTarget(){
	return RT;
}