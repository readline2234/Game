#include "stdafx.h"
#include "Player.h"

Player::Player(float x, float y, float z) : GameObject(x,y,z)
{
}
Player::Player(Vec3 vector)
{
	//GameObject(vector);
}
void Player::Draw()
{
	GameObject::DrawModel();
}

void Player::MoveForward()
{
	if (enabled)
	{
		if (acc > 10)
			velocity = 0.5;

		SetPosZ(GetPosZ() + (velocity * acc / 1000) + booster);
		//SetPosZ(GetPosZ() + 1);
	}
}

void Player::GainRPM()
{
	if (enabled)
	{
		if (rpm > MAX_RPM_LOWER)	//3900
		{
			rpm = MAX_RPM;
			return;
		}

		switch (gear)
		{
		case 1: {
			rpm += FIRST_GEAR_RPM_GAIN;
			break;
		}
		case 2: {
			rpm += SECOND_GEAR_RPM_GAIN;
			break;
		}
		case 3: {
			rpm += THIRD_GEAR_RPM_GAIN;
			break;
		}
		case 4: {
			rpm += FOURTH_GEAR_RPM_GAIN;
			break;
		}
		}
	}
}
void Player::GainAcc()
{
	if (enabled)
	{
		if (rpm > MAX_RPM_LOWER)		//3990 bylo jest 3900
		{
			acc += OVER_RPM_ACC_GAIN;		//?
			return;
		}

		switch (gear)
		{
		case 1: {
			acc += FIRST_GEAR_ACC_GAIN;
			break;
		}
		case 2: {
			acc += SECOND_GEAR_ACC_GAIN;
			break;
		}
		case 3: {
			acc += THIRD_GEAR_ACC_GAIN;
			break;
		}
		case 4: {
			acc += FOURTH_GEAR_ACC_GAIN;
			break;
		}
		}
	}
}

void Player::LooseSpeed()
{
	if (velocity > 0.02);
	velocity /= SPEED_LOSS;
	//velocity = 0;
}
void Player::LooseRPM()
{
	if (rpm > MIN_RPM)
	{
		switch (gear)
		{
		case 1: {
			rpm -= FIRST_GEAR_RPM_LOSS;
			break;
		}
		case 2: {
			rpm -= SECOND_GEAR_RPM_LOSS;
			break;
		}
		case 3: {
			rpm -= THIRD_GEAR_RPM_LOSS;
			break;
		}
		case 4: {
			rpm -= FOURTH_GEAR_RPM_LOSS;
			break;
		}
		}
	}
}
void Player::LooseAcc()
{
	if (acc > 0)
	{
		switch (gear)
		{
		case 1: {
			acc -= FIRST_GEAR_ACC_LOSS;
			break;
		}
		case 2: {
			acc -= SECOND_GEAR_ACC_LOSS;
			break;
		}
		case 3: {
			acc -= THIRD_GEAR_ACC_LOSS;
			break;
		}
		case 4: {
			acc -= FOURTH_GEAR_ACC_LOSS;
			break;
		}
		}
	}
}
void Player::LooseBooster()
{
	if (booster > 1)
	{
		booster -= BOOSTER_LOSS;
	}
	if (booster < 1 && booster > 0)
	{
		booster -= 0.01;
	}
}

void Player::GearUp()
{
	cout << shifts[0] << endl;
	cout << shifts[1] << endl;
	cout << shifts[2] << endl;
	cout << shifts[3] << endl;

	if (gear < GEARS_NUMBER)
	{
		float temp_rpm = rpm / PERF_RPM;
		temp_rpm = 1-abs(1 - temp_rpm);

		shifts[gear] = temp_rpm ;	//migawka zmiany biegu
		
		booster = temp_rpm * BOOSTER_VALUE;

		gear++;
		rpm = RPM_AFTER_SHIFT;

		

	}
	


}

float Player::GetSpeed()
{
	return speed;
}
float Player::GetVelocity()
{
	return velocity;
}
float Player::GetRPM()
{
	return rpm;
}
float Player::GetGear()
{
	return gear;
}
float Player::GetAcc()
{
	return acc;
}
float Player::GetBooster()
{
	return booster;
}
bool  Player::GetEnabled()
{
	return enabled;
}

void Player::SetSpeed(float s)
{
	speed = s;
}
void Player::SetVelocity(float v)
{
	velocity = v;
}
void Player::SetEnabled()
{
	enabled = 1;
}
