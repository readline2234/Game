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
	SetPosZ(GetPosZ() + (velocity * acc/1000));
	//SetPosZ(GetPosZ() + 1);
}

void Player::LooseSpeed()
{
	velocity /= 1.05;
}

void Player::LooseRPM()
{
	if (rpm > 800)
	{
		rpm -= 1.1;
	}
}
void Player::GainRPM()
{
	if (rpm > 3900)
	{
		rpm = 4000;
		return;
	}

	switch (gear)
	{
	case 1: {
		rpm += 9;
		break;
	}
	case 2: {
		rpm += 5;
		break;
	}
	case 3: {
		rpm += 3 ;
		break;
	}
	case 4: {
		rpm += 2;
		break;
	}
	}
}

void Player::LooseAcc()
{
	if (acc > 0)
	{
		acc -= 1.1;
	}
}
void Player::GainAcc()
{

	if (rpm > 3990)		//TU POWINNA BYC STALA MAX RPM
	{
		acc += 1.1;		//TU POWINNA BYC STALA LOSE ACC
		return;
	}

	switch (gear)
	{
	case 1: {
		acc += 7;
		break;
	}
	case 2: {
		acc += 5;
		break;
	}
	case 3: {
		acc += 3;
		break;
	}
	case 4: {
		acc += 2;
		break;
	}
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
		float temp_rpm = rpm / 2500;
		temp_rpm = 1-abs(1 - temp_rpm);

		shifts[gear] = temp_rpm ;	//migawka zmiany biegu
		gear++;
		rpm = 800;
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

void Player::SetSpeed(float s)
{
	speed = s;
}
void Player::SetVelocity(float v)
{
	velocity = v;
}
