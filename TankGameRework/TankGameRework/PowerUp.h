#pragma once
#include <stdlib.h>
#include <time.h>

#include "Transform.h"

class PowerUp : public Transform
{
public:
	float upTime, respawnTime, useTime;
	int powerType, randomSeed;

	PowerUp();

	void RandomNumber();

};
