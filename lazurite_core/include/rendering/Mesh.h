#pragma once
#include "component/AComponent.h"
#include "component\Camera.h"
#include "rendering\Primitive.h"

class Mesh : public AComponent {
	std::vector<std::shared_ptr<Primitive>> primitives;

public:
	Mesh();
	Mesh(std::vector<std::shared_ptr<Primitive>> primitives);
	~Mesh();
	virtual void Tick(float deltaTime);
	void Draw(Camera& camera, Transform& camTransform, Transform& modelTransform);
};

