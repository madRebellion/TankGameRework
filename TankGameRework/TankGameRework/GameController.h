#pragma once
#include "Tank.h"

class GameController
{
public:
	Tank *player;

	float xScreen, yScreen;

	GameController();
	~GameController();

	void ScreenWrap(void);
	void Die(void);
	void Respawn(void);
};