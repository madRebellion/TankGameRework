#include "Transform.h"

// Contructor
Transform::Transform()
{
	DefaultPosition();
	DefaultRotation();
	DefaultScaling();
}

void Transform::Rotate()
{
	if (rotateLeft)
	{
		SetRotation(0.0f, 0.0f, -1.0f);
	}
	if (rotateRight)
	{
		SetRotation(0.0f, 0.0f, 1.0f);
	}
}

float Transform::GetTransform()
{
	return
		position.x,
		position.y,
		position.z,
		rotation.x,
		rotation.y,
		rotation.z,
		scale.x,
		scale.y,
		scale.z;
}

#pragma region Position Overloads


void Transform::SetPosition(float _x, float _y)
{
	position.x += _x;
	position.y += _y;
	position.z = 0.0f;
}

void Transform::SetPosition(float _x, float _y, float _z)
{
	position.x += _x;
	position.y += _y;
	position.z += _z;
}

void Transform::SetPosition(Vector3 pos)
{
	position = pos;
}

#pragma endregion

void Transform::SetRotation(float _x, float _y, float _z)
{
	rotation.x += _x;
	rotation.y += _y;
	rotation.z += _z;
}
void Transform::SetRotation(Vector3 _rot)
{
	rotation = _rot;
}


// Only used by constructor. Makes code cleaner, nothing more (yet..).
void Transform::DefaultPosition()
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
}
void Transform::DefaultRotation()
{
	rotateLeft = false;
	rotateRight = false;
	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;
}
void Transform::DefaultScaling()
{
	scale.x = 0.0f;
	scale.y = 0.0f;
	scale.z = 0.0f;
}