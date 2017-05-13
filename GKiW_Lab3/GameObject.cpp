#include "stdafx.h"
#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{

}
GameObject::GameObject(float x, float y, float z)
{
	pos = new Vec3(x, y, z);
	rot = new Vec3(0, 0, 0);
	scal = new Vec3(1, 1, 1);
}
GameObject::GameObject(Vec3 vector)
{
	pos = new Vec3;
	*pos = vector;		//moze byc blad
	rot = new Vec3(0, 0, 0);
	scal = new Vec3(1, 1, 1);
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
void GameObject::SetPosXYZ(Vec3 vector)
{
	* pos = vector;
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

void GameObject::SetRot(float x, float y, float z)
{
	rot->SetXYZ(x, y, z);
}
void GameObject::SetRot(Vec3 vector)
{
	rot->SetXYZ(vector.GetX(), vector.GetY(), vector.GetZ());
}

void GameObject::SetScal(float x, float y, float z)
{
	scal->SetXYZ(x, y, z);
}
void GameObject::SetScal(Vec3 vector)
{
	scal->SetXYZ(vector.GetX(), vector.GetY(), vector.GetZ());
}

void GameObject::Draw()
{
	glPushMatrix();

		
		glRotatef(rot->GetX(), 1.0f, 0.0f, 0.0f);
		glRotatef(rot->GetY(), 0.0f, 1.0f, 0.0f);
		glRotatef(rot->GetZ(), 0.0f, 0.0f, 1.0f);
		glScalef(scal->GetX(), scal->GetY(), scal->GetZ());
		glutSolidCube(1.0f);
	glPopMatrix();
}

void GameObject::LoadModel(char * fp,char *ip)
{
	model = new Model(fp,ip);
}
void GameObject::DrawModel()
{

	model->Draw(*pos,*rot,*scal);
}

