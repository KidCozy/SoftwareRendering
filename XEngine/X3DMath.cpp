#include "X3DMath.h"



void Translate(Object& target, VECTOR3D offset_) {

	MATRIX TranslateMat;

	TranslateMat.M11_ = 1;
	TranslateMat.M22_ = 1;
	TranslateMat.M33_ = 1;
	TranslateMat.M44_ = 1;

	TranslateMat.M41_ = offset_.x;
	TranslateMat.M42_ = offset_.y;
	TranslateMat.M43_ = offset_.z;

	target.Transform.M41_ += TranslateMat.M41_;
	target.Transform.M42_ -= TranslateMat.M42_;
	target.Transform.M43_ += TranslateMat.M43_;


}

void Rotate(Object& target, VECTOR3D offset_) {

	if (offset_.x > 0.0f || offset_.x < 0.0f) {
		target.Transform.M22_ += cosf(offset_.x);
		target.Transform.M23_ += sinf(offset_.x);
		target.Transform.M32_ += -sinf(offset_.x);
		target.Transform.M33_ += cosf(offset_.x);

		
		
	}

	if (offset_.y > 0 || offset_.y < 0) {
		target.Transform.M11_ += cosf(offset_.y);
		target.Transform.M13_ += sinf(offset_.y);
		target.Transform.M31_ += -sinf(offset_.y);
		target.Transform.M33_ += cosf(offset_.y);
	

	
	}

	if (offset_.z > 0 || offset_.z < 0) {
		target.Transform.M11_ += cosf(offset_.y);
		target.Transform.M12_ += -sinf(offset_.y);
		target.Transform.M21_ += sinf(offset_.y);
		target.Transform.M22_ += cosf(offset_.y);
	}


	for (auto tri : target.Mesh.tris) {
		//cout << "Rotate : " << tri.p[0].x << endl;
		MultiplyMatrixVector(tri.p[0], target.Transform);
		MultiplyMatrixVector(tri.p[1], target.Transform);
		MultiplyMatrixVector(tri.p[2], target.Transform);
	}

	DrawMatrix(target.Transform);

	// cos a, 0, sin a, 0,
	//   0  , 1,   0  , 0,
	//-sin a, 0, cos a, 0,
	//   0  , 0,   0  , 1



}