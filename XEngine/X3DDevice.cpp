#include "X3DDevice.h"
#include"stdafx.h"
BYTE* mScreenBits;

X3DDevice::X3DDevice(HWND hWnd, HDC mDC) {
//	int bufferSize = mRenderer->GetHeight() * mRenderer->GetWidth();
//	mZBuffer = new float[bufferSize];
}


X3DDevice::X3DDevice() {

}

void X3DDevice::Init(HWND hWnd) {


	hScreenDC = GetDC(hWnd);
	hMemoryDC = CreateCompatibleDC(hScreenDC);

	BITMAPINFO bitInfo;
	memset(&bitInfo, 0, sizeof(BITMAPINFO));

	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo.bmiHeader.biWidth = mWidth;
	bitInfo.bmiHeader.biHeight = -mHeight;

	bitInfo.bmiHeader.biPlanes = 1;
	bitInfo.bmiHeader.biBitCount = 32;
	bitInfo.bmiHeader.biCompression = BI_RGB;

	hDIBitmap = CreateDIBSection(hMemoryDC, &bitInfo, DIB_RGB_COLORS, (void**)&mScreenBits, NULL, 0);
	hPrimaryBit = (HBITMAP)SelectObject(hMemoryDC, hDIBitmap);


}

void X3DDevice::Release(HWND hWnd) {

	mIsRender = FALSE;

	DeleteObject(hPrimaryBit);
	DeleteObject(hDIBitmap);
	ReleaseDC(hWnd, hScreenDC);
	ReleaseDC(hWnd, hMemoryDC);
}

void X3DDevice::SetColor(BYTE R, BYTE G, BYTE B)
{
	mCurrentColor = RGB(B, G, R);
}



void X3DDevice::SwapChain() {

	HDC tempDC;

	//tempDC = hScreenDC;
	//hScreenDC = hMemoryDC;
//	hMemoryDC = hScreenDC;

	BitBlt(hScreenDC, 0, 0, mWidth, mHeight, hMemoryDC, 0, 0, SRCCOPY);
}

void X3DDevice::DrawFrameRate()
{
}

X3DDevice::~X3DDevice(){
}
