#include "stdafx.h"
#include "XEngineRenderer.h"

#define DrawBH DrawLineByBresenHam(POINT2D from, POINT2D to);

using namespace align;

ULONG mCurrentColor;

TestStar Group[16];
TestStar* star = Group;

mesh meshBox;
Object BoxObject;


triangle FillTri = {
	{0,100, 300, 100, 100,0}

};

VECTOR2D vertices[4] = {
	{-10, 10},
	{10, 10},
	{10,-10},
	{-10,-10}
};

VECTOR2D* verticesPtr = vertices;


MATRIX BoxMat;	



VECTOR3D BoxVertices[8] = {
	{-100.0f, 100.0f, 1.0f},  
	{ 100.0f, 100.0f, 1.0f},  
	{ -100.0f, -100.0f, 1.0f },
	{ 100.0f, -100.0f, 1.0f},
	{ -100.0f, 100.0f, 1.0f},
	{ 100.0f, 100.0f, 1.0f },
	{ -100.0f, -100.0f, 1.0f },
	{ 100.0f, -100.0f, 1.0f},
};

VECTOR3D* BoxVerticesPtr = BoxVertices;

void XEngineRenderer::Init(HWND hWnd) {
	mDevice_.Init(hWnd);

	GetClientRect(hWnd, &mRect);

	mWidth = mRect.right;
	mHeight = mRect.bottom;
	mIsRender = TRUE;

	mTheta = 0.0f;
	
	//-----------------------------------//

	meshBox.tris = {

		// SOUTH
		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// EAST                                                      
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// NORTH                                                     
		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// WEST                                                      
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// TOP                                                       
		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

	};

	BoxObject.Mesh = meshBox;
	

}


VECTOR2D start = { 0,0 };
VECTOR2D mDest;

VECTOR2D start2 = { 127,32 };
VECTOR2D dest2 = { 73,-22 };

VECTOR3D RotateVar = { 50,1,0 };
VECTOR3D TranslateVar = { 1,1,1 };
VECTOR3D ScaleVar = { 1,1,1 };
// 렌더 구간
void XEngineRenderer::Render(float pDelta)
{
	delta = pDelta;

	mDevice_.SetColor(255, 255, 255);
	Clear();

	mDevice_.SetColor(0, 0, 0);
	RenderObject(BoxObject);

	Rotate(BoxObject, RotateVar);
//	cout << RotateVar.x << endl;
	
	mDevice_.SetColor(255, 0, 255);
	PixelOut(0, -100);
	mDevice_.SwapChain();
}
void XEngineRenderer::Release(HWND hWnd)
{
	mDevice_.Release(hWnd);
	mDevice_.~X3DDevice();
	this->~XEngineRenderer();
}
void XEngineRenderer::PixelOut(int x, int y)
{
	if (!IsInArea(x, y)) return;

	ULONG* dest = (ULONG*)mScreenBits;
	DWORD offset = mWidth * mHeight / 2 + mWidth / 2 + x + mWidth * -y;
	*(dest + offset) = mCurrentColor;
}
void XEngineRenderer::Clear()
{
	/*int x = -mWidth / 2, y = -mHeight / 2;
	mDevice_.SetColor(255, 0, 0);
	for (int i = x; i < 256; i++) {
		for (int j = y; j < 256; j++) {
			PixelOut(i, j);
		}
	}*/
//	mDevice_.SetColor(255, 255, 255);
	ULONG* dest = (ULONG*)mScreenBits;
	DWORD area = (mWidth * mHeight) * sizeof(ULONG);

	ULONG value = mCurrentColor;

	area /= 4;

	while (area--) {
		*dest++ = value;
	}
	return;
}
void XEngineRenderer::RayFill()
{

	int x0, x1, x2;
	int y0, y1, y2;

	x0 = vertices[0].x; y0 = vertices[0].y;
	x1 = vertices[1].x; y1 = vertices[1].y;
	x2 = vertices[2].x; y2 = vertices[2].y;

	if (y1 < y0) {
		std::swap(x1, x0);
		std::swap(y1, y0);
	}
	
	if (y2 < y0) {
		std::swap(x2, x0);
		std::swap(y2, y0);
	}

	if (y2 < y1) {
		std::swap(x2, y1);
		std::swap(y2, y1);
	}
	
	float dx1 = 0.0f, dx2 = 0.0f, dx3 = 0.0f;

	if (y1 - y0 > 0) dx1 = (x1 - x0) / (y1 - y0); else dx1 = 0.0f;
	if (y2 - y0 > 0) dx2 = (x2 - x0) / (y2 - y0); else dx2 = 0.0f;
	if (y2 - y1 > 0) dx3 = (x2 - x1) / (y2 - y1); else dx3 = 0.0f;

	VECTOR2D S, E;

	S = E = { x0,y0 };

	if (dx1 > dx2) {
	//	for (; S.y <= y1; S.y++, E.y++, S.x += dx2, E.x += dx1)

	}

	ULONG* dest = (ULONG*)mScreenBits;

	DWORD area = (vertices[0].x*vertices[2].x) * sizeof(ULONG);
	
	ULONG value = RGB(255,255, 255);

	while (area--) {
		*dest++ = value;
	}
	return;

}
void XEngineRenderer::DrawStar(TestStar* star)
{
	for (int i = 0; i < 16; i++) {
		//star[i].mPos = star[i].mPos * ;

		

		int x = star[i].mPos.x / star[i].mPos.z;
		int y = star[i].mPos.y / star[i].mPos.z;

		star[i].mPos.z += 0.1f;

		if (x < 256)
			ChangeLineColor(BG_GREEN, FG_BLACK);
		else
			ChangeLineColor(BG_RED, FG_BLACK);

		cout << "STAR (" << star[i].mPos.x << ", " << star[i].mPos.y << ", " << star[i].mPos.z << ")" << endl;
		

		PixelOut(x,y);
	}
	
	ChangeLineColor(BG_BLACK, FG_BLACK);
	system("cls");
}
void XEngineRenderer::LineDraw(VECTOR2D start, VECTOR2D dest) {

	int W = dest.x - start.x;
	int H = dest.y - start.y;

	int angle = H / W;

	int x = start.x;


	if (W > H) {
		int y = angle * start.x;
		for (x = start.x; x < dest.x; ++x) {
			
			PixelOut(x, y);
			
		}
	}


	
}
void XEngineRenderer::DrawPlane(VECTOR2D * vertices)
{
	for (int i = 0; i < 4; i++) {
		if (i + 1 < 4)
			DrawGDILine(vertices[i], vertices[i + 1]);
		else
			DrawGDILine(vertices[i], vertices[0]);
	}
}

void XEngineRenderer::RenderObject(Object obj) {
	DrawMesh(obj.Mesh);

	DrawMatrix(obj.Transform);
}

void XEngineRenderer::DrawMesh(mesh mesh)
{
	MATRIX matRotZ, matRotX;

	mTheta += 0.5f * delta;



	matRotZ.M11_ = cosf(mTheta);
	matRotZ.M12_ = sinf(mTheta);
	matRotZ.M21_ = -sinf(mTheta);
	matRotZ.M22_ = cosf(mTheta);
	matRotZ.M33_ = 1;
	matRotZ.M44_ = 1; 

	matRotX.M11_ = 1;
	matRotX.M22_ = cosf(mTheta);
	matRotX.M23_ = sinf(mTheta);
	matRotX.M32_ = -sinf(mTheta);
	matRotX.M33_ = cosf(mTheta);
	matRotX.M44_ = 1;
	
	for (auto tri : mesh.tris) {
	//	VECTOR3D MovX = { 0,1 * mTheta * 0.1f,0 };
		triangle ProjectedTri, TranslatedTri, RotateX, RotateXZ;

		
		MultiplyMatrixVector(tri.p[0], RotateX.p[0], matRotX);
		MultiplyMatrixVector(tri.p[1], RotateX.p[1], matRotX);
		MultiplyMatrixVector(tri.p[2], RotateX.p[2], matRotX);


		MultiplyMatrixVector(RotateX.p[0], RotateXZ.p[0], matRotZ);
		MultiplyMatrixVector(RotateX.p[1], RotateXZ.p[1], matRotZ);
		MultiplyMatrixVector(RotateX.p[2], RotateXZ.p[2], matRotZ);


		TranslatedTri = RotateXZ;
		TranslatedTri.p[0].z = RotateXZ.p[0].z + 2.0f;
		TranslatedTri.p[1].z = RotateXZ.p[1].z + 2.0f;
		TranslatedTri.p[2].z = RotateXZ.p[2].z + 2.0f;




		MultiplyMatrixVector(TranslatedTri.p[0], ProjectedTri.p[0], cam.mMat);
		MultiplyMatrixVector(TranslatedTri.p[1], ProjectedTri.p[1], cam.mMat);
		MultiplyMatrixVector(TranslatedTri.p[2], ProjectedTri.p[2], cam.mMat);
	
		
		ProjectedTri.p[0].x += 1.0f; ProjectedTri.p[0].y += 1.0f;
		ProjectedTri.p[1].x += 1.0f; ProjectedTri.p[1].y += 1.0f;
		ProjectedTri.p[2].x += 1.0f; ProjectedTri.p[2].y += 1.0f;

		ProjectedTri.p[0].x *= 0.5f* (float)mWidth;
		ProjectedTri.p[0].y *= 0.5f* (float)mHeight;

		ProjectedTri.p[1].x *= 0.5f* (float)mWidth;
		ProjectedTri.p[1].y *= 0.5f* (float)mHeight;

		ProjectedTri.p[2].x *= 0.5f* (float)mWidth;
		ProjectedTri.p[2].y *= 0.5f* (float)mHeight;

		
		FillTriangle(ProjectedTri.p[0].x, ProjectedTri.p[0].y,
			ProjectedTri.p[1].x, ProjectedTri.p[1].y,
			ProjectedTri.p[2].x, ProjectedTri.p[2].y, RGB(0,0,0));

		DrawTriangle(ProjectedTri.p[0].x, ProjectedTri.p[0].y,
			ProjectedTri.p[1].x, ProjectedTri.p[1].y,
			ProjectedTri.p[2].x, ProjectedTri.p[2].y);
	}
}

void XEngineRenderer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	
	VECTOR2D xy1 = { x1,y1 };
	VECTOR2D xy2 = { x2,y2 };
	VECTOR2D xy3 = { x3,y3 };

	DrawGDILine(xy1, xy2);
	DrawGDILine(xy2, xy3);
	DrawGDILine(xy3, xy1);
	
	DrawFillPoly(x2+5,y2+5, RGB(0, 0, 0));
	SetPixel(mDevice_.PeekDC(), x2+5, y2+5, RGB(255, 0, 0));
}

void XEngineRenderer::FillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, COLORREF color) {
	
//	mDevice_.SetColor(GetRValue(color), GetGValue(color), GetBValue(color));

	VECTOR3D xy1 = { x1,y1 };
	VECTOR3D xy2 = { x2,y2 };
	VECTOR3D xy3 = { x3,y3 };

	if (y1 > y2) {
		std::swap(xy1, xy2);
	}
	if (y2 > y3) {
		std::swap(xy2, xy3);
	}
	if (y3 > y1) {
		std::swap(xy3, xy1);
	}
	if (y1 > y3) {
		std::swap(xy1, xy3);
	}
	if (y3 > y2) {
		std::swap(xy3, xy2);
	}
	if (y2 > y1) {
		std::swap(xy2, xy1);
	}


	if (xy2.y == xy1.y)
	{
		cout << "Bottom flat side" << endl;
		fillBottomFlatTriangle(xy1, xy2, xy3);
	}

	else if (xy3.y == xy2.y)
	{
		cout << "Top flat side" << endl;
		fillTopFlatTriangle(xy1, xy2, xy3);
	}
	else
	{
		cout << "Non flat side" << endl;
		VECTOR3D v4 = {(int)(xy3.x + ((float)(xy2.y - xy3.y) / (float)(xy1.y - xy3.y)) * (xy1.x - xy3.x), xy2.y) };
		
		fillBottomFlatTriangle(xy3, xy2, v4);
		fillTopFlatTriangle(xy2, v4, xy1);
	}

}

bool XEngineRenderer::Collide(VECTOR2D point, triangle tri) {
	
	int x1, x2, x3, y1, y2, y3;
	int px, py;

	px = point.x;
	py = point.y;

	x1 = tri.p[0].x;
	x2 = tri.p[1].x;
	x3 = tri.p[2].x;

	y1 = tri.p[0].y;
	y2 = tri.p[1].y;
	y3 = tri.p[2].y;

	// 2 4 1
	// 1 2 4

	// 1 2 3
	

	float areaOrig = abs((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1));
	float area1 = abs((x1 - px)*(y2 - py) - (x2 - px)*(y1 - py));
	float area2 = abs((x2 - px)*(y3 - py) - (x3 - px)*(y2 - py));
	float area3 = abs((x3 - px)*(y1 - py) - (x1 - px)*(y3 - py));


	if (area1 + area2 + area3 == areaOrig) {
		return true;
	}
	return false;

}

void XEngineRenderer::Line(VECTOR2D start, VECTOR2D dest) {

	int x0, x1;
	int y0, y1;

	float W, H;
	
	x0 = start.x;
	x1 = dest.x;

	y0 = start.y;
	y1 = dest.y;

	W = x1 - x0;
	H = y1 - y0;

	float Slope = H / W;

	

	if (W < 0 || H < 0 && false) {				// 시작점과 끝점의 위치를 바꾼다. (start와 dest가 뒤집어진 경우)
	
		
		std::swap(start, dest);
	}

	ShowCurrentPoints(start,0,L"start");
	ShowCurrentPoints(dest,20,L"dest");

	if (Slope >= 0 && Slope <= 1) {						// X 변화량이 큰 경우 // 1사이 인경우 (x변화량이 클때)
		
		cout << "X" << endl;
		int x = 0;
		int y = 0;

		if (dest.x == 0) {
			for (int y = start.y; y < dest.y; y++) {
				x = Slope * y;
				PixelOut(x, y);
			}
		}

		if (W > H) { //x 변화량이 y 변화량보다 큰경우
			for (int x = start.x; x < dest.x; x++) {
				y = Slope * x;
				PixelOut(x, y);
		//		cout << x << ", " << y << endl;

			}
		}
		else {
			for (int y = start.y; x < dest.y; y++) {
				x = Slope * y;
				PixelOut(x, y);
			}
		}


	}

	else {								// Y 변화량이 큰 경우 // 기울기가 1보다 작은경우
		int y = 0;
		int x = 0;

		if (Slope == INFINITY) {
			cout << "MIDDLE" << endl;
			for (int y = start.y; y < dest.y; y++) {
				PixelOut(0, y);
			}
		}

		if (W < H) {
			for (int x = start.x; x < dest.x; x++) {
				y = Slope * x;
				PixelOut(x, y);
		//		cout << x << ", " << y << endl;

			}
		}
		
		else {
			for (int y = start.y; x < dest.y; y++) {
				x = Slope * y;
				PixelOut(x, y);
			}
		}
	

	}


}

bool XEngineRenderer::DrawLine(VECTOR2D start, VECTOR2D dest)
{
	int x = start.x;
	int y = start.y;

	int W = dest.x - start.x;
	int H = dest.y - start.y;

	int F = 2 * H - W;

	int df1 = 2 * H;
	int df2 = 2 * (H - W);

	for (x = start.x; x <= dest.x; ++x) {
		PixelOut(x, y);

		if (F < 0) {
			F += df1;
		}
		else {
			++y;
			F += df2;
		}
	}
	return true;
}

void XEngineRenderer::DrawGDILine(VECTOR2D start, VECTOR2D dest)
{
	int w = (mWidth / 2);
	int h = (mHeight / 2);
	MoveToEx(mDevice_.PeekDC(), start.x, start.y, NULL);
	LineTo(mDevice_.PeekDC(), dest.x, dest.y);

}

void XEngineRenderer::DrawFillPoly(int x, int y, COLORREF color) {

//	FloodFill(mDevice_.PeekDC(), x, y, color);

}

void XEngineRenderer::fillBottomFlatTriangle(VECTOR3D v1, VECTOR3D v2, VECTOR3D v3)
{
		float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
		float invslope2 = (v2.x - v1.x) / (v2.y - v1.y);

		float curx1 = v1.x;
		float curx2 = v1.x;

		for (int scanlineY = v1.y; scanlineY < v3.y; scanlineY++)
		{
			VECTOR2D start, dest;

			start = { (int)curx1, scanlineY };
			dest = { (int)curx2, scanlineY };

			DrawGDILine(start, dest);

			curx1 += invslope1;
			curx2 += invslope2;
		}

}




void XEngineRenderer::fillTopFlatTriangle(VECTOR3D v1, VECTOR3D v2, VECTOR3D v3)
{
		float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
		float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

		float curx1 = v3.x;
		float curx2 = v3.x;

		for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--)
		{
			VECTOR2D start = { (int)curx1, scanlineY };
			VECTOR2D dest = { (int)curx2, scanlineY };

			DrawGDILine(start, dest);
			
			
			curx1 -= invslope1;
			curx2 -= invslope2;
		}


}




bool XEngineRenderer::IsInArea(int x, int y)
{
	
	return (abs(x) < (mWidth / 2)) && (abs(y) < mHeight / 2);
}

XEngineRenderer::XEngineRenderer() : cam(PrimeCamera(90, 1000.0f, 0.1f, mHeight, mWidth))
{
	
}
XEngineRenderer::~XEngineRenderer()
{
}