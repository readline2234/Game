#pragma once
#include "GameObject.h"


class Player : public GameObject {
private:

public:
	Player(float x, float y, float z);
	Player(Vec3 vector);

	void Draw();
};