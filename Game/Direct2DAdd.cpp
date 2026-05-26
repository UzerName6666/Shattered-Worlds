#include "win.h"
#include "Direct2DAdd.h"
#include <wincodec.h>
#include <wrl/client.h>
#pragma comment(lib, "Windowscodecs.lib")
#pragma comment(lib, "ole32.lib")
ID2D1Bitmap* LoadImage(std::wstring Path, ID2D1RenderTarget* pRenderTarget){
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