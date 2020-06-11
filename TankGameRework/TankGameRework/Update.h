#pragma once
#include <Windows.h>
#include "GameController.h"

struct Update
{
	// Used by the InputController function
	MSG msg;

	bool playing = true;

	void UpdateGame(Tank *player);
	void InputController(Tank *player);
};
