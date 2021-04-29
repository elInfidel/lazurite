#include "rendering/mesh.h"

Mesh::Mesh() {}
Mesh::~Mesh() {}

Mesh::Mesh(std::vector<std::shared_ptr<Primitive>> primitives) {
	this->primitives = primitives;
}

void Mesh::Tick(float deltaTime) {}

void Mesh::Draw(Camera& camera, Transform& camTransform, Transform& modelTransform) {
	for (auto primitive : this->primitives) {
		primitive.get()->Draw(camera, camTransform, modelTransform);
	}
}