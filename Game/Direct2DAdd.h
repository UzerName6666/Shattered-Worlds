#pragma once
#include "Direct2D.h"
#include <string>

ID2D1Bitmap* LoadImage(std::wstring Path, ID2D1RenderTarget* pRenderTarget);