#include "stdafx.h"
#include "TestStar.h"

#include<iostream>

using namespace std;

TestStar::TestStar()
{
	mPos = VECTOR4D();

	for (int i = 0; i < 3; i++) {
		mPos.M[i] = rand();
	}

//	cout << "STAR (" << mPos.x << ", " << mPos.y << ", " << mPos.z << ")" << endl;
	

}
TestStar::~TestStar()
{
}

void TestStar::Render() {

}