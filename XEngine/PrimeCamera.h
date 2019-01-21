#pragma once
#include"XMath.h"
class PrimeCamera
{
private:
	
	
	// Projection Matrix
	float mFov;
	float mFar;
	float mNear;
	float mAspectRatio;
	float mFovRad;

	

public:

	MATRIX mMat;

	void LookPosition();
	void SetFov(float Fov) { mFov = Fov; }
	void SetFar(float Far) { mFar = Far; }
	void SetNear(float Near) { mNear = Near; }

	void TransformInMatrix();
	void Rasterize();

	PrimeCamera(float fov, float fa, float ne, int height, int width) : mFov(fov), mFar(fa), mNear(ne) {
		mAspectRatio = (float)height / (float)width;
		mFovRad = 1.0f / tanf(mFov*0.5f / 180.0f*3.14159f);

		mMat.M11_ = mAspectRatio * mFovRad;
		mMat.M22_ = mFovRad;
		mMat.M33_ = mFar / (mFar - mNear);
		mMat.M43_ = (-mFar * mNear) / (mFar - mNear);
		mMat.M34_ = 1.0f;
		mMat.M44_ = 0.0f;
	
	
	};
	~PrimeCamera();
};

