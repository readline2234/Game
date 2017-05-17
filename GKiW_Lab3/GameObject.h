#pragma once
#include "stdafx.h"
#include "Vec3.h"
#include "Model.h"
#include "Texture.h"

class GameObject {
private:
	Vec3 * pos;
	Vec3 * rot;
	Vec3 * scal;

	Model * model;

public:
	GameObject();
	GameObject(float x, float y, float z);
	GameObject(Vec3 vector);

	void SetPosX(float x);
	void SetPosY(float y);
	void SetPosZ(float z);
	void SetPosXYZ(float x, float y, float z);
	void SetPosXYZ(Vec3 vector);
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	Vec3 GetPosXYZ();

	void SetRot(float x, float y, float z);
	void SetRot(Vec3 vector);

	void SetScal(float x, float y, float z);
	void SetScal(Vec3 vector);

	void LoadModel(char * fp,char *ip);
	void DrawModel();
};