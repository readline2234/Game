#pragma once
#include "stdafx.h"
#include "Vec3.h"

class GameObject {
private:
	Vec3 * pos;
	Vec3 * rot;
	Vec3 * scale;
public:
	GameObject();
	GameObject(float x, float y, float z);
	GameObject(Vec3 vector);
	void SetPosX(float x);
	void SetPosY(float y);
	void SetPosZ(float z);
	void SetPosXYZ(float x, float y, float z);
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	Vec3 GetPosXYZ();
	void Scale();
	void Rotate();
	void Draw();
};