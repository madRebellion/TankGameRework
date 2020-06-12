#pragma once
#include "Tank.h"
#include "PowerUp.h"

class GameController
{
public:
	Tank *player;
	PowerUp *powerUp;

	float xScreen, yScreen;

	GameController();
	~GameController();

	void ScreenWrap(void);
	void Die(void);
	void Respawn(void);
};