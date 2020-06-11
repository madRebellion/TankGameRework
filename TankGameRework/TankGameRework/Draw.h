#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Tank.h"

struct Draw
{
	static float tankVert[], cannonVert[];
	static float tankColour[], cannonColour[];
	void DrawGame(Tank *player);
};
