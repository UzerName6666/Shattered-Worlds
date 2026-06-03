#pragma once
#include "Direct2D.h"
#include "Vector2D.h"
namespace ShatteredEngine{

    class Camera{
	protected:
	    ID2D1RenderTarget* pRenderTarget;
	    bool ChangePos;
	    Vector2D Cur;
	    Vector2D MaxSize;
	    Vector2D WindowSize;
	public:

	    bool SetPosition(Vector2D cord);
	    bool SetRoomSize(Vector2D size);

	    Camera();
	    Camera(ID2D1RenderTarget* pRenderTarget);

	    void Draw(Vector2D cord, ID2D1Bitmap* sprite);

	    bool InBound(Vector2D lu, Vector2D rd);
	    void Reset();

	    ID2D1RenderTarget* GetRenderTarget();
    };
}