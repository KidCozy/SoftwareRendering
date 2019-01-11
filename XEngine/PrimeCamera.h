#pragma once
#include"XMath.h"
class PrimeCamera
{
private:
	MATRIX mMat;
	float mFov;

public:
	void LookPosition();
	void SetFov();
	void TransformInMatrix();
	void Rasterize();

	PrimeCamera();
	~PrimeCamera();
};

