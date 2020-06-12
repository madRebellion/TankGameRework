#include "PowerUp.h"

PowerUp::PowerUp()
{
	srand((time(NULL)));
	randomSeed = rand() % 2 - 2;
	position.x = randomSeed;
	position.y = randomSeed;
}

void PowerUp::RandomNumber()
{
	srand(randomSeed);
	randomSeed = rand() % 2;
}
