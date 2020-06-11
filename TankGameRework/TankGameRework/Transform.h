#pragma once

struct Vector3 { float x, y, z; };

struct Transform
{

public:
	Vector3 position, rotation, scale;
	bool rotateRight, rotateLeft;

	// Constructor for defaults
	Transform();

	void Rotate(void);

protected:
	void DefaultPosition(void);
	void DefaultRotation(void);
	void DefaultScaling(void);

	float GetTransform();
	// Overloaded position setters/mutators
	void SetPosition(float _x, float _y);
	void SetPosition(float _x, float _y, float _z);
	void SetPosition(Vector3 pos);

	void SetRotation(float _x, float _y, float _z);
	void SetRotation(Vector3 _rot);

};

