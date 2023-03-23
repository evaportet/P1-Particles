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

	const int MIN_EMISSION_RATE = 100;
	const int MAX_EMISSION_RATE = 1000;
	const int MIN_LIFE = 1;
	const int MAX_LIFE = 5;

	float xyAngle;
	float xzAngle;
	float yzAngle;

	const int MIN_XY_ANGLE = 0;
	const int MAX_XY_ANGLE = 180;
	const int MIN_XZ_ANGLE = 0;
	const int MAX_XZ_ANGLE = 360;
	const int MIN_YZ_ANGLE = 0;
	const int MAX_YZ_ANGLE = 180;

	static const int nParts = 20;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	
	glm::vec3 positions[nParts];
	glm::vec3 velocities[nParts];
	//contenedor de acceleraciones para las colisiones
	glm::vec3 accelerations[nParts];

	int totalTime;
};