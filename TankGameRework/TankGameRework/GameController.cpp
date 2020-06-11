#include "GameController.h"

GameController::GameController()
{
	player = new Tank;
	player->cannon = new Cannon;
}

GameController::~GameController()
{
	delete player->cannon;
	player->cannon = NULL;

	delete player;
	player = NULL;
}

void GameController::ScreenWrap()
{
	// Handle screen wrap for xAxis
	if (player->position.x < -2.75f)
	{
		player->position.x = 2.75;
	}
	if (player->position.x > 2.75f)
	{
		player->position.x = -2.75f;
	}

	// Handle screen wrap for yAxis
	if (player->position.y > 1.75)
	{
		player->position.y = -2.0f;
	}
	if (player->position.y < -2.0f)
	{
		player->position.y = 1.75f;
	}
}