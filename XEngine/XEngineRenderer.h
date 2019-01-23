#pragma once
#include"X3DDevice.h"
#include"XMath.h"
#include"Mesh.h"
#include"PrimeCamera.h"
#include"PrimeEngine.h"
#include"TestStar.h"

#include"ConsoleLib.h"

#include<Windows.h>

using namespace std;


namespace align {
	enum AXIS {
		CENTER,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
	};
}

using namespace align;

class XEngineRenderer
{

private:

	X3DDevice mDevice_;
	float delta;
	RECT mRect;
	float mTheta;
	PrimeCamera cam;

public:

	void SetParams();
	void Init(HWND hWnd);
	void Render(float delta);
	void Release(HWND hWnd);

	//Primitive
	void SetColor(BYTE R, BYTE G, BYTE B);
	
	void PixelOut(int x, int y);
	void Clear();

	void RayFill();

	void DrawStar(TestStar* star);

	
	void Line(VECTOR2D start, VECTOR2D dest);
	bool DrawLine(VECTOR2D start, VECTOR2D dest);
	void LineDraw(VECTOR2D start, VECTOR2D dest);
	void Draw2DPlane(PLANE2D plane_);
	void DrawLineByBresenHam(POINT2D from, POINT2D to, COLORREF color);

	void DrawPlane(VECTOR2D* vertices);
	void DrawBox(VECTOR3D* vertices);
	void DrawMesh(mesh vertices);
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
	void FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, COLORREF color);

	

	void ShowPoints(VECTOR2D pnt) {

		wchar_t wszText[512] = { 0 };
		swprintf(wszText, 512, L"(%d, %d)", pnt.x, pnt.y);
		::TextOut(mDevice_.PeekDC(), pnt.x+(mWidth/2), (-pnt.y+(mHeight/2)), wszText, wcslen(wszText));
	}

	void ShowCurrentPoints(VECTOR2D pnt, int offset, const wchar_t* descrpt) {
		wchar_t wszText[512] = { 0 };
		swprintf(wszText, 512, L"%s : (%d, %d)", descrpt ,pnt.x, pnt.y);
		::TextOut(mDevice_.PeekDC(), 0, 0+offset, wszText, wcslen(wszText));
	}


	void Draw2DSquare(SQUARE2D sqr_);

	void Translate(VECTOR3D offset_);
	void Translate(float x, float y, float z);

	

	void DrawGizmos(AXIS Center);
	
	void DrawGDILine(VECTOR2D start, VECTOR2D dest);
	void DrawGDILine(VECTOR3D start, VECTOR3D dest);

	bool IsInArea(int x, int y);
	bool Collide(VECTOR2D point, triangle tri);

	XEngineRenderer();
	XEngineRenderer(HWND hWnd);
	~XEngineRenderer();


// 기타 디버그용 도형 선언
private:
	PLANE2D temp;

};

