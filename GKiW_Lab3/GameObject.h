#pragma once
class GameObject {
private:
	float PosX;
	float PosY;
	float PosZ;
public:
	GameObject();
	//GameObject(vec3 vector);
	GameObject(float x, float y, float z);
	void SetPosX(float x);
	void SetPosY(float y);
	void SetPosZ(float z);
	void SetPos(float x, float y, float z);
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	//vec3 GetPos();
	void Scale();
	void Rotate();
	void Draw();
};