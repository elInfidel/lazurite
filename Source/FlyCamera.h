#pragma once
#include "Camera.h"

class FlyCamera : public Camera
{
public:
	FlyCamera();
	~FlyCamera();

	virtual void Update(float deltaTime);

private:
	const float movementSpeed = 10.0f;
	const float sensitivity = 0.05f;

	float yaw, pitch;

	void CalculateRotation(float deltaTime);
	void CalculateMovement(float deltaTime);
};

