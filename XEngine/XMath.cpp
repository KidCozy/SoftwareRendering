#include"XMath.h"

using namespace std;


#define WORLDMAT CMWorldMatrix
#define PROJECTIONMAT CMProjectionMatrix
//------------------------------------------------------------//
MATRIX CMWorldMatrix = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};

MATRIX CMProjectionMatrix = {
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
};


MATRIX_TYP operator*(MATRIX_TYP p1, VECTOR4D p2) {
	MATRIX_TYP retVal;

	retVal.M11_ = p1.M11_ * p2.x;
	retVal.M12_ = p1.M12_ * p2.y;
	retVal.M13_ = p1.M13_ * p2.z;
	retVal.M14_ = p1.M14_ * p2.w;
	
	retVal.M21_ = p1.M21_ * p2.x;
	retVal.M22_ = p1.M22_ * p2.y;
	retVal.M23_ = p1.M23_ * p2.z;
	retVal.M24_ = p1.M24_ * p2.w;

	retVal.M31_ = p1.M31_ * p2.x;
	retVal.M32_ = p1.M32_ * p2.y;
	retVal.M33_ = p1.M33_ * p2.z;
	retVal.M34_ = p1.M34_ * p2.w;

	retVal.M41_ = p1.M41_ * p2.x;
	retVal.M42_ = p1.M42_ * p2.y;
	retVal.M43_ = p1.M43_ * p2.z;
	retVal.M44_ = p1.M44_ * p2.w;

	return retVal;
}

MATRIX_TYP operator*(MATRIX_TYP p1, MATRIX_TYP p2) {

	MATRIX_TYP retVal;

	retVal.M11_ = p1.M11_ * p2.M11_ + p1.M12_* p2.M21_ + p1.M13_ * p2.M31_ + p1.M14_*p2.M41_;
	retVal.M12_ = p1.M11_ * p2.M12_ + p1.M12_* p2.M22_ + p1.M13_ * p2.M32_ + p1.M14_*p2.M42_;
	retVal.M13_ = p1.M11_ * p2.M13_ + p1.M12_* p2.M23_ + p1.M13_ * p2.M33_ + p1.M14_*p2.M43_;
	retVal.M14_ = p1.M11_ * p2.M14_ + p1.M12_* p2.M24_ + p1.M13_ * p2.M34_ + p1.M14_*p2.M44_;

	retVal.M21_ = p1.M21_ * p2.M11_ + p1.M22_* p2.M21_ + p1.M23_ * p2.M31_ + p1.M24_*p2.M41_;
	retVal.M22_ = p1.M21_ * p2.M12_ + p1.M22_* p2.M22_ + p1.M23_ * p2.M32_ + p1.M24_*p2.M42_;
	retVal.M23_ = p1.M21_ * p2.M13_ + p1.M22_* p2.M23_ + p1.M23_ * p2.M33_ + p1.M24_*p2.M43_;
	retVal.M24_ = p1.M21_ * p2.M14_ + p1.M22_* p2.M24_ + p1.M23_ * p2.M34_ + p1.M24_*p2.M44_;

	retVal.M31_ = p1.M31_ * p2.M11_ + p1.M32_* p2.M21_ + p1.M33_ * p2.M31_ + p1.M34_*p2.M41_;
	retVal.M32_ = p1.M31_ * p2.M12_ + p1.M32_* p2.M22_ + p1.M33_ * p2.M32_ + p1.M34_*p2.M42_;
	retVal.M33_ = p1.M31_ * p2.M13_ + p1.M32_* p2.M23_ + p1.M33_ * p2.M33_ + p1.M34_*p2.M43_;
	retVal.M34_ = p1.M31_ * p2.M14_ + p1.M32_* p2.M24_ + p1.M33_ * p2.M34_ + p1.M34_*p2.M44_;

	retVal.M41_ = p1.M41_ * p2.M11_ + p1.M42_* p2.M21_ + p1.M43_ * p2.M31_ + p1.M44_*p2.M41_;
	retVal.M42_ = p1.M41_ * p2.M12_ + p1.M42_* p2.M22_ + p1.M43_ * p2.M32_ + p1.M44_*p2.M42_;
	retVal.M43_ = p1.M41_ * p2.M13_ + p1.M42_* p2.M23_ + p1.M43_ * p2.M33_ + p1.M44_*p2.M43_;
	retVal.M44_ = p1.M41_ * p2.M14_ + p1.M42_* p2.M24_ + p1.M43_ * p2.M34_ + p1.M44_*p2.M44_;

	return retVal;

}


MATRIX LocalToWorldMatrix(MATRIX local_)
{
	MATRIX world_;

	world_ = local_ * WORLDMAT;

	return world_;
	
}




void Translate(LPTRANSFORM target, VECTOR3D offset_) {
	
}


void DrawMatrix(MATRIX mat)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << mat.M[i*j] << ", ";
		}
		cout << endl;
	}
}
