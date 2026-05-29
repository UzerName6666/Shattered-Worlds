#include "Engine.h"
ShatteredEngine::Camera::Camera(){
	pRenderTarget = nullptr;
}

ShatteredEngine::Camera::Camera(ID2D1RenderTarget* RenderTarget){
	pRenderTarget = RenderTarget;
	WindowSize.x = pRenderTarget -> GetSize().width;
	WindowSize.y = pRenderTarget -> GetSize().height;
	MaxSize.x = WindowSize.x;
	MaxSize.y = WindowSize.y;
	Cur.x = 0;
	Cur.y = 0;
	ChangePos = true;
}

void ShatteredEngine::Camera::Reset(){
	ChangePos = true;
}

void ShatteredEngine::Camera::Draw(Vector2D cord, ID2D1Bitmap* sprite){
	if(pRenderTarget && sprite){
		Vector2D Cordx(cord.x, cord.y);
		Vector2D Cordy(cord.x + sprite -> GetSize().width, cord.y + sprite -> GetSize().height);
		if(InBound(Cordx, Cordy)){
			Cordx = Vector2D(cord.x - Cur.x, cord.x - Cur.x + sprite -> GetSize().width);
			Cordy = Vector2D(cord.y - Cur.y, cord.y - Cur.y + sprite -> GetSize().height);
			pRenderTarget -> DrawBitmap(sprite, D2D1::RectF(Cordx.x, Cordy.x, Cordx.y, Cordy.y));
		}
		ChangePos = false;
	}
}

bool ShatteredEngine::Camera::InBound(Vector2D lu, Vector2D rd){
	if(!pRenderTarget){
		return false;
	}
	if(rd.x < lu.x || rd.y < lu.y){
		return false;
	}
	if(lu.x > Cur.x + WindowSize.x || rd.x < Cur.x){
		return false;
	}
	if(lu.y > Cur.y + WindowSize.y || rd.y < Cur.y){
		return false;
	}
	return true;
}

bool ShatteredEngine::Camera::SetPosition(Vector2D size){
	if(!pRenderTarget){
		return false;
	}
	if(!ChangePos){
		return false;
	}
	Cur.x = size.x - WindowSize.x;
	Cur.y = size.y - WindowSize.y;
	if(Cur.x < 0){
		Cur.x = 0;
	}
	if(Cur.x > MaxSize.x - WindowSize.x){
		Cur.x = MaxSize.x - WindowSize.x;
	}
	if(Cur.y < 0){
		Cur.y = 0;
	}
	if(Cur.y > MaxSize.y - WindowSize.y){
		Cur.y = MaxSize.y - WindowSize.y;
	}
	return true;
}

bool ShatteredEngine::Camera::SetRoomSize(Vector2D cord){
	if(!ChangePos || !pRenderTarget){
		return false;
	}
	MaxSize.x = cord.x;
	MaxSize.y = cord.y;
	if(MaxSize.y < WindowSize.x){
		MaxSize.x = WindowSize.x;
	}
	if(MaxSize.y < WindowSize.y){
		MaxSize.y = WindowSize.y;
	}
	return true;
}

ID2D1RenderTarget* ShatteredEngine::Camera::GetRenderTarget(){
	return pRenderTarget;
}