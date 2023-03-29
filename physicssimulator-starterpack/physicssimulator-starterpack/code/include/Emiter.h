#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <vector>
#include <PrimitiveManager.h>
#include "EulerStep.h"

class Emiter
{
protected:
	graphics::ParticlesPrimitive* particlesPrim;
	int emissionRate;
	float particleLife;
	//int nParticles = emissionRate * particleLife;
	int nParts;
	int currentMaxPart;

	glm::vec3 gravity = glm::vec3(0.f, -9.81f, 0.f);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> velocities;
	//contenedor de acceleraciones para las colisiones
	std::vector<glm::vec3> accelerations;

	const int MIN_EMISSION_RATE = 150;
	const int MAX_EMISSION_RATE = 2000;
	const int MIN_LIFE = 1;
	const int MAX_LIFE = 5;
	
	void RegeneratePrim(int part);

public:
	Emiter(int em, float pl);
	~Emiter();

	glm::vec3 GetParticlePosition(int indice);
	glm::vec3 GetParticleVelocity(int indice);
	glm::vec3 GetParticleAcceleration(int indice);
	
	void SetParticlePosition(int index, glm::vec3 newP);
	void SetParticleVelocity(int index, glm::vec3 newV);
	void SetParticleAcceleration(int index, glm::vec3 newA);

	int GetNumParticles();

	virtual void UpdateParticle(int index, glm::vec3 pos, glm::vec3 vel, glm::vec3 a, float dt) = 0;
	
	virtual void Update(float dt) = 0;
	virtual void RenderGUI() = 0;
	void Render();
	void ToggleVisibility(bool value);
};

