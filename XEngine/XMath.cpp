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


MATRIX_TYP operator*(MATRIX p1, VECTOR4D p2) {
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

VECTOR3D operator*=(VECTOR3D& vect, float flt) {
	vect.x *= flt;
	vect.y *= flt;
	vect.z *= flt;

	return vect;
}

VECTOR3D operator*(VECTOR3D vect, float flt) {
	
	vect.x *= flt;
	vect.y *= flt;
	vect.z *= flt;

	return vect;
}


MATRIX LocalToWorldMatrix(MATRIX local_)
{
	MATRIX world_;

	world_ = local_ * WORLDMAT;

	return world_;
	
}

void MultiplyMatrixVector(VECTOR3D & i, VECTOR3D & o, MATRIX & m) {
	o.x = i.x * m.M11_ + i.y * m.M21_ + i.z * m.M31_ + m.M41_;
	o.y = i.x * m.M12_ + i.y * m.M22_ + i.z * m.M32_ + m.M42_;
	o.z = i.x * m.M13_ + i.y * m.M23_ + i.z * m.M33_ + m.M43_;
	float w = i.x * m.M14_ + i.y * m.M24_ + i.z * m.M34_ + m.M44_;

	if (w != 0.0f) {
		o.x /= w; o.y /= w; o.z /= w;
	}
}


void MultiplyMatrixVector(VECTOR3D & o, MATRIX & m) {
	o.x = m.M11_ + m.M21_ + m.M31_ + m.M41_;
	o.y = m.M12_ + m.M22_ + m.M32_ + m.M42_;
	o.z = m.M13_ + m.M23_ + m.M33_ + m.M43_;
	float w = m.M14_ + m.M24_ + m.M34_ + m.M44_;

	if (w != 0.0f) {
		o.x /= w; o.y /= w; o.z /= w;
	}
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
