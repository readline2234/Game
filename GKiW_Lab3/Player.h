#pragma once
#include "GameObject.h"


class Player : public GameObject {
private:


	Vec3 * dir;
	//player.dir.x = 0.0f;
	//player.dir.y = 0.0f;
	//player.dir.z = -1.0f;

	float speed = 1.50f;
	float velocity=0;


public:
	Player(float x, float y, float z);
	Player(Vec3 vector);

	void MoveForward();
	void LooseSpeed();

	void Draw();

	float GetSpeed();
	float GetVelocity();

	void SetSpeed(float s);
	void SetVelocity(float v);
};