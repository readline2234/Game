#include "stdafx.h"
#include "Vec3.h"

Vec3::Vec3()
{

}
Vec3::Vec3(float x, float y, float z)
{
	X = x;	Y = y; Z = z;
}
void SetX(float x)
{
	X = x;
}
void SetY(float y)
{
	Y = y;
}
void SetZ(float z)
{
	Z = z;
}
void SetXYZ(float x, float y, float z)
{
	X = x;	Y = y; Z = z;
}
float GetX()
{
	return X;
}
float GetY()
{
	return Y;
}
float GetZ()
{
	return Z;
}
Vec3 GetXYZ()
{
	// dopisac metode, poprawic to co wyzej
}


std::ostream & operator << (std::ostream &wyjscie, const Vec3 &v)
{
	return wyjscie << std::endl << "X: " << v.X << "\tY: " << v.Y << "\tZ: " << v.Z << std::endl;
}