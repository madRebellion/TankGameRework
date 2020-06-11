#include "Draw.h"

// Player
float Draw::tankVert[18] = {
	-0.1f, -0.1f, 0.0f,
	0.2f, -0.1f, 0.0f,
	-0.1f, 0.1f, 0.0f,
	-0.1f, 0.1f, 0.0f,
	0.2f, -0.1f, 0.0f,
	0.2f, 0.1f, 0.0f
};

// Cannon
float Draw::cannonVert[18] = {
	-0.05f, -0.05f, 0.0f,
	0.1f, -0.05f, 0.0f,
	-0.05f, 0.05f, 0.0f,
	-0.05f, 0.05f, 0.0f,
	0.1f, -0.05f, 0.0f,
	0.1f, 0.05f, 0.0f
};

// Red
float Draw::tankColour[24] = {
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f
};

// White
float Draw::cannonColour[24] = {
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f
};

void Draw::DrawGame(Tank *player)
{
	// Open the vertex/colour array states to be thrown at OpenGL
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glMatrixMode(GL_MODELVIEW);

	// Main tank object
	// 3 verts per triangle - x, y, z
	glVertexPointer(3, GL_FLOAT, 0, tankVert);
	// 4 colour options - r,g,b,a
	glColorPointer(4, GL_FLOAT, 0, tankColour);
	glLoadIdentity();
	glTranslatef(player->position.x, player->position.y, -5.0f);
	glRotatef(player->rotation.z, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// This is needed to draw each object
	////////////////////////////////////////////////////////////////////////////////////
	// Cannon object
	//
	glMatrixMode(GL_MODELVIEW);
	glVertexPointer(3, GL_FLOAT, 0, cannonVert);
	glColorPointer(4, GL_FLOAT, 0, cannonColour);
	glLoadIdentity();
	glTranslatef(player->position.x, player->position.y, -5.0f);
	glRotatef(player->cannon->rotation.z, 0.0f, 0.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//
	////////////////////////////////////////////////////////////////////////////////////

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

}