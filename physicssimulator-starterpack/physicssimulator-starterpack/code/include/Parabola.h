#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include "imgui/imgui.h"

class ParabolaSim : public Simulator {
public:
	ParabolaSim();
	~ParabolaSim();

	void Update(float dt) override;
	void RenderUpdate() override;
	void RenderGui() override;
	void EulerSolver(float dt);

private:
	graphics::ParticlesPrimitive* particlesPrim;
	float emissionRate = 100.0f;
	float particleLife = 1.0f;
	int nParticles = emissionRate * particleLife;
	static const int nParts = 2;
	
	glm::vec3 positions[nParts];
	glm::vec3 velocities[nParts];

	glm::vec3 currentPos;
	glm::vec3 currentVel;

	glm::vec3 previousPos;
	glm::vec3 previousVel;

	glm::vec3 acceleration;

	int totalTime;
};