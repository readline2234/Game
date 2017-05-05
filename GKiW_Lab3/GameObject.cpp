#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
{

}
GameObject::GameObject(float x, float y, float z)
{
	pos = new Vec3;
	pos->SetXYZ(x, y, z);
}
GameObject::GameObject(Vec3 vector)
{
	pos = new Vec3;
	*pos = vector;		//moze byc blad
}
void GameObject::SetPosX(float x)
{
	pos->SetX(x);
}
void GameObject::SetPosY(float y)
{
	pos->SetY(y);
}
void GameObject::SetPosZ(float z)
{
	pos->SetZ(z);
}
void GameObject::SetPosXYZ(float x, float y, float z)
{
	pos->SetXYZ(x, y, z);
}
float GameObject::GetPosX()
{
	return pos->GetX();
}
float GameObject::GetPosY()
{
	return pos->GetY();
}
float GameObject::GetPosZ()
{
	return pos->GetZ();
}
Vec3 GameObject::GetPosXYZ()
{
	return * pos;
}	
//sprawdzic to
void GameObject::Scale()
{

}
void GameObject::Rotate()
{

}
void GameObject::Draw()
{
	glPushMatrix();
		glutSolidCube(1.0f);
	glPopMatrix();
}