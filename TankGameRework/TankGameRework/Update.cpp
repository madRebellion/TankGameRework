#include "Update.h"

void Update::UpdateGame(GameController *controller)
{
	InputController(controller);

	/*if (player->tankSpeed != 0.0f)
	{
		player->CalculateMovement();
	}
	player->Rotate();
	player->cannon->Rotate();*/

	controller->player->CalculateMovement();
}

// Handles player inputs and OS messages
void Update::InputController(GameController *controller)
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		// When we press the 'X' (close window) button on title bar, 
		// we want to close the application
		if (msg.message == WM_QUIT)
		{
			playing = false;
		}

		// Player inputs - When a key is pressed
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.wParam)
			{
			case VK_ESCAPE:
				playing = false;
				break;
			case 'W':
				controller->player->tankSpeed = 0.01f;
				break;
			case 'S':
				controller->player->tankSpeed = -0.005f;
				break;
			case 'A':
				controller->player->rotateRight = true;
				break;
			case 'D':
				controller->player->rotateLeft = true;
				break;
			case 'Q':
				controller->player->cannon->rotateRight = true;
				break;
			case 'E':
				controller->player->cannon->rotateLeft = true;
				break;
			default:
				break;
			}
		}

		// Player inputs - When a key is released
		// Mainly used to reset values set with WM_KEYDOWN
		if (msg.message == WM_KEYUP)
		{
			switch (msg.wParam)
			{
			case 'W':
				controller->player->tankSpeed = 0.0f;
				break;
			case 'S':
				controller->player->tankSpeed = 0.0f;
				break;
			case 'A':
				controller->player->rotateRight = false;
				break;
			case 'D':
				controller->player->rotateLeft = false;
				break;
			case 'Q':
				controller->player->cannon->rotateRight = false;
				break;
			case 'E':
				controller->player->cannon->rotateLeft = false;
				break;
			}
		}

	}
	else
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}