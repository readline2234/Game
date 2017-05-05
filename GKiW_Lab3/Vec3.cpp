#include "stdafx.h"
#include "Vec3.h"

Vec3::Vec3()
{

}
Vec3::Vec3(float x, float y, float z)
{
	X = x;	Y = y; Z = z;
}
void Vec3::SetX(float x)
{
	X = x;
}
void Vec3::SetY(float y)
{
	Y = y;
}
void Vec3::SetZ(float z)
{
	Z = z;
}
void Vec3::SetXYZ(float x, float y, float z)
{
	X = x; Y = y; Z = z;
}
float Vec3::GetX()
{
	return X;
}
float Vec3::GetY()
{
	return Y;
}
float Vec3::GetZ()
{
	return Z;
}
std::ostream & operator << (std::ostream &wyjscie, const Vec3 &v)
{
	return wyjscie << std::endl << "X: " << v.X << "\tY: " << v.Y << "\tZ: " << v.Z << std::endl;
}