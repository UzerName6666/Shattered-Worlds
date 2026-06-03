#include "Main.h"
#include <wincodec.h>
#include <wrl/client.h>
#pragma comment(lib, "Windowscodecs.lib")
#pragma comment(lib, "ole32.lib")
ID2D1Bitmap* ShatteredEngine::Window::LoadImage(std::wstring Path){
	ID2D1Bitmap* Image = nullptr;
	HRESULT hr = CoInitialize(nullptr);
	Microsoft::WRL::ComPtr<IWICImagingFactory> IFactory;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		&IFactory
	);
	if(SUCCEEDED(hr)){
		IWICBitmapDecoder* pDecoder;
		hr = IFactory->CreateDecoderFromFilename(
			Path.c_str(),
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
		if(SUCCEEDED(hr)){
			IWICBitmapFrameDecode* pFrameDecode = nullptr;
			pDecoder -> GetFrame(0, &pFrameDecode);
			IWICBitmapSource* pConvertedSource = nullptr;
			IWICFormatConverter *pConverter = nullptr;
			IFactory->CreateFormatConverter(&pConverter);
			hr = pConverter -> Initialize(
				pFrameDecode,
				GUID_WICPixelFormat32bppPRGBA,
				WICBitmapDitherTypeNone,
				NULL,
				0.0f,
				WICBitmapPaletteTypeMedianCut
			);
			if(SUCCEEDED(hr)){
				pRenderTarget -> CreateBitmapFromWicBitmap(pConverter, NULL, &Image);
				pConverter -> Release();
			}
			pDecoder -> Release();
		}
		IFactory -> Release();
	}
	return Image;
}

ShatteredEngine::Window::Window(){
    pRenderTarget = nullptr;
}

bool ShatteredEngine::Window::Init(HINSTANCE hInstance, ID2D1Factory* pFactory){
    if(pRenderTarget){
        Logger::Write(Logger::Error, L"ReInit of window detected");
        return false;
    }
    if(!pFactory){
        Logger::Write(Logger::Error, L"Failed to create window, pFactory = nullptr");
        return false;
    }
    WNDCLASSEXW wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = hInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = GameManager::WNDProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"WinMainClass";
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	RegisterClassExW(&wc);
	hwnd = CreateWindowExW(
		WS_EX_APPWINDOW,
		wc.lpszClassName,
		L"Shattered Worlds",
		WS_OVERLAPPEDWINDOW,
		screenWidth / 2 - 160, screenHeight / 2 - 160, 306, 328,
		NULL, NULL, hInstance, NULL
	);
    RECT rc;
	GetClientRect(hwnd, &rc);
	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
	pFactory->CreateHwndRenderTarget(
	D2D1::RenderTargetProperties(),
	D2D1::HwndRenderTargetProperties(hwnd, size),
	&pRenderTarget
	);
    Logger::Write(Logger::Message, L"Window created");
    return true;
}

void ShatteredEngine::Window::Show(){
	ShowWindow(hwnd, SW_SHOW);
}

void ShatteredEngine::Window::Hide(){
	ShowWindow(hwnd, SW_HIDE);
}

ShatteredEngine::Window::Window(HINSTANCE hInstance, ID2D1Factory* pFactory){
    pRenderTarget = nullptr;
    Init(hInstance, pFactory);
}

HWND ShatteredEngine::Window::GetHWND(){
    return hwnd;
}

ID2D1HwndRenderTarget* ShatteredEngine::Window::GetRenderTarget(){
    return pRenderTarget;
}

bool ShatteredEngine::Window::Loaded(){
    return pRenderTarget;
}

