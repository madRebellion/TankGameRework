#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GameController.h"

struct Draw
{
	static float tankVert[], cannonVert[], powerUpVert[];
	static float tankColour[], cannonColour[], powerUpColour[];
	void DrawGame(GameController *controller);
};
