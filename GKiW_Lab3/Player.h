#pragma once
#include "GameObject.h"

class Player : public GameObject {
private:

	const float MIN_RPM = 800;
	const float PERF_RPM = 2500;
	const float MAX_RPM = 4000;
	const float MAX_RPM_LOWER = 3900;	//pomocnicza zmienna, troche mniej niz max
	const float RPM_AFTER_SHIFT = 1000;
	int GEARS_NUMBER = 4;

	const float FIRST_GEAR_RPM_GAIN =	40;
	const float SECOND_GEAR_RPM_GAIN = 20;
	const float THIRD_GEAR_RPM_GAIN = 15;
	const float FOURTH_GEAR_RPM_GAIN = 5;

	const float FIRST_GEAR_RPM_LOSS = 25;
	const float SECOND_GEAR_RPM_LOSS = 10;
	const float THIRD_GEAR_RPM_LOSS = 8;
	const float FOURTH_GEAR_RPM_LOSS = 2;

	const float FIRST_GEAR_ACC_GAIN = 20;
	const float SECOND_GEAR_ACC_GAIN = 15;
	const float THIRD_GEAR_ACC_GAIN = 10;
	const float FOURTH_GEAR_ACC_GAIN = 10;
	const float OVER_RPM_ACC_GAIN = 1.1;	//zbyt duze (maksymalne) obroty, predkosc nie rosnie

	const float FIRST_GEAR_ACC_LOSS = 5;	//odwortnie	- najmniejsdza
	const float SECOND_GEAR_ACC_LOSS = 5;
	const float THIRD_GEAR_ACC_LOSS = 7;
	const float FOURTH_GEAR_ACC_LOSS = 10;	// najwieksza

	const float SPEED_LOSS = 1.05;
	const float ACC_LOSS = 1.1;
	const float BOOSTER_LOSS = 1.0;
	const float BOOSTER_VALUE = 10;
	float speed = 1;
	float velocity = 0;

	int gear = 1;
	float rpm = MIN_RPM;
	float acc = 0;
	float booster = 0;

	float shifts[3] = {0};	//ewentualnie dynamicznie dla roznych pojazdow - shifts[GEARS_NUMBER]
	

public:
	Player(float x, float y, float z);
	Player(Vec3 vector);

	float GetSpeed();
	float GetVelocity();
	float GetRPM();
	float GetGear();
	float GetAcc();
	float GetBooster();

	void SetSpeed(float s);
	void SetVelocity(float v);

	void MoveForward();
	void LooseSpeed();

	void GainRPM();
	void LooseRPM();

	void GainAcc();
	void LooseAcc();

	void GearUp();

	void LooseBooster();
	

	void Draw();

};