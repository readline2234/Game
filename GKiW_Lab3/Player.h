#pragma once
#include "GameObject.h"


class Player : public GameObject {
private:


	//Vec3 * dir;
	//player.dir.x = 0.0f;
	//player.dir.y = 0.0f;
	//player.dir.z = -1.0f;

	float speed = 1.50f;
	float velocity=0;

	int gear = 1;
	float rpm = 800;
	float acc = 0;

	float FIRST_GEAR_CONST = 0.8;		//dopisac wiecej sta³ych
	float SECOND_GEAR_CONST = 0.5;
	float THIRD_GEAR_CONST = 0.3;
	float FOURTH_GEAR_CONST = 0.1;

	int GEARS_NUMBER = 4;

	float shifts[3] = {0};	//ewentualnie dynamicznie dla roznych pojazdow - shifts[GEARS_NUMBER]
	

public:
	Player(float x, float y, float z);
	Player(Vec3 vector);

	float GetSpeed();
	float GetVelocity();
	float GetRPM();
	float GetGear();
	float GetAcc();

	void SetSpeed(float s);
	void SetVelocity(float v);

	void MoveForward();
	void LooseSpeed();

	void GainRPM();
	void LooseRPM();

	void GainAcc();
	void LooseAcc();

	void GearUp();

	void Draw();

};