#pragma once
#include<vector>
#include"XMath.h"
using namespace std;

struct triangle {
	VECTOR3D p[3];
};

typedef struct mesh {
	vector<triangle> tris;
}*MESH;