#pragma once
#include <Windows.h>
#include <math.h>
#include "Transform.h"
#include "Cannon.h"

class Tank : public Transform
{
public:

	Cannon *cannon;

	float tankSpeed = 0.0f;

	void CalculateMovement(void);
};
