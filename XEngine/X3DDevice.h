#pragma once
#include<Windows.h>
#include"PrimeEngine.h"


extern BYTE* mScreenBits;
extern ULONG mCurrentColor;

class X3DDevice
{
private:
	float* mZBuffer;

	HDC hScreenDC, hMemoryDC;
	HBITMAP hPrimaryBit, hDIBitmap;


public:
	X3DDevice();
	X3DDevice(HWND hWnd, HDC mDC);

	void Init(HWND hWnd);
	void Release(HWND hWnd);

	void SetColor(BYTE R, BYTE G, BYTE B);

	void SwapChain();
	void DrawFrameRate();

	HDC PeekDC() { return hMemoryDC; }
	
	~X3DDevice();


};

