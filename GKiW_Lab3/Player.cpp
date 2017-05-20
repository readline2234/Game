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
	SetPosZ(GetPosZ() + velocity);
	//SetPosZ(GetPosZ() + 1);
}

void Player::LooseSpeed()
{
	velocity /= 1.05;
}


float Player::GetSpeed()
{
	return speed;
}
float Player::GetVelocity()
{
	return velocity;
}

void Player::SetSpeed(float s)
{
	speed = s;
}
void Player::SetVelocity(float v)
{
	velocity = v;
}

//player.pos.x += player.dir.x * player.velM * .1f;