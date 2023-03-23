#pragma once
#include <Simulator.h>
#include <RenderPrims.h>
#include <vector>
#include <PrimitiveManager.h>

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
	
	virtual void Update(float dt) = 0;
	virtual void RenderGUI() = 0;
	void Render();
};

