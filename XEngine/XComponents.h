#pragma once
#include"Mesh.h"
#include"PrimeCamera.h"



typedef struct object {
	MATRIX Transform;
	mesh Mesh;

} Object, *LPObject;