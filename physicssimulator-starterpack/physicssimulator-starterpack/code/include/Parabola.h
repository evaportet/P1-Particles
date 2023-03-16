#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <vector>
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
	static const int nParts = 20;
	
	glm::vec3 positions[nParts];
	glm::vec3 velocities[nParts];
	//contenedor de acceleraciones para las colisiones
	glm::vec3 accelerations[nParts];

	glm::vec3 currentPos;
	glm::vec3 currentVel;

	glm::vec3 previousPos;
	glm::vec3 previousVel;

	glm::vec3 acceleration;

	int totalTime;

	const int MIN_EMISSION_RATE = 100;
	const int MAX_EMISSION_RATE = 1000;
	const int MIN_LIFE = 1;
	const int MAX_LIFE = 5;
};