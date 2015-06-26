#pragma once
#include "glm/glm.hpp"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "ShaderProgram.h"

using glm::vec3;
using glm::vec4;

namespace GPUParticle
{
	struct Particle
	{
		Particle() : lifetime(1), lifespan(0) {}

		vec3 position;
		vec3 velocity;
		float lifetime;
		float lifespan;
	};
}

class GPUParticleEmitter
{
public:
	GPUParticleEmitter();
	virtual ~GPUParticleEmitter();

	void Initialize(unsigned int maxParticles, float lifespanMin,
		float lifespanMax, float velocityMin, float velocityMax, float startSize,
		float endSize, const vec4& startColor, const vec4& endColor);

	void Draw(float time, Camera& camera);

protected:
	void CreateBuffers();
	void CreateUpdateProgram();
	void CreateDrawProgram();

	GPUParticle::Particle* particles;

	unsigned int maxParticles;

	Transform transform;

	float lifespanMin;
	float lifespanMax;

	float velocityMin;
	float velocityMax;

	float startSize;
	float endSize;

	vec4 startColor;
	vec4 endColor;

	unsigned int activeBuffer;
	unsigned int vao[2];
	unsigned int vbo[2];

	ShaderProgram* drawProgram;
	ShaderProgram* updateProgram;

	float lastDrawTime;

};

