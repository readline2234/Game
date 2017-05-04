#pragma once
#include <iostream>

class Vec3 {
private:
	float X;
	float Y;
	float Z;
public:
	Vec3();
	Vec3(float x, float y, float z);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetXYZ(float x, float y, float z);
	float GetX();
	float GetY();
	float GetZ();
	Vec3 GetXYZ();

	friend std::ostream & operator << (std::ostream &wyjscie, const Vec3 &s);
};

//TODO: Vec3(&Vec3);	//konstruktor kopiujacy????
