#include "X3DMath.h"


void Translate(VECTOR3D& target, VECTOR3D offset_) {

	MATRIX TranslateMat;

	TranslateMat.M11_ = 1;
	TranslateMat.M22_ = 1;
	TranslateMat.M33_ = 1;
	TranslateMat.M44_ = 1;

	TranslateMat.M41_ = offset_.x;
	TranslateMat.M42_ = offset_.y;
	TranslateMat.M43_ = offset_.z;

	target.x += TranslateMat.M41_;
	target.y -= TranslateMat.M42_;
	target.z += TranslateMat.M43_;


}

void Rotate(Object& target, VECTOR3D offset_) {

	if (offset_.x > 0.0f || offset_.x < 0.0f) {
		MATRIX xMat;
		xMat.M11_ = cosf(offset_.x);
		xMat.M13_ = sinf(offset_.x);
		xMat.M31_ = -sinf(offset_.x);
		xMat.M33_ = cosf(offset_.x);

		MultiplyMatrixVector()

	}

	if (offset_.y > 0 || offset_.y < 0) {

	}

	if (offset_.z > 0 || offset_.z < 0) {

	}


	// cos a, 0, sin a, 0,
	//   0  , 1,   0  , 0,
	//-sin a, 0, cos a, 0,
	//   0  , 0,   0  , 1



}