#include "Tank.h"

void Tank::CalculateMovement()
{
	if (rotateLeft || rotateRight)
	{
		Rotate();
		cannon->rotation = rotation;
	}
	if (cannon->rotateLeft || cannon->rotateRight)
	{
		cannon->Rotate();
	}

	// Calculates for diagional movements
	position.x += (tankSpeed * cos(rotation.z * 0.01745f));
	position.y += (tankSpeed * sin(rotation.z * 0.01745f));
}