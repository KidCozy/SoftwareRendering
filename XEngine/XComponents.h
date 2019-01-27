#pragma once
#include"Mesh.h"
#include"PrimeCamera.h"



typedef struct object {
	MATRIX Transform;
	MESH Mesh;
} Object, *LPObject;