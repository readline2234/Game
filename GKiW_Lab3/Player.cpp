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
