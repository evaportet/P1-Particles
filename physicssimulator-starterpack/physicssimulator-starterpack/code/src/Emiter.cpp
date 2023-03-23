#include "Emiter.h"

extern graphics::PrimitiveManager manager;

Emiter::Emiter(int em, float pl) : emissionRate(em), particleLife(pl)
{
	/*for (int i = 0; i < nParts; i++)
	{
		positions[i] = glm::vec3(rand() % 5);
		velocities[i] = glm::vec3(rand() % 5);
		accelerations[i] = glm::vec3(0.0f, -0.981f, 0.0f);
	}*/
	nParts = 0;
	currentMaxPart = 1000;
	particlesPrim = manager.NewParticles(nParts);
	particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = nParts;
}

Emiter::~Emiter()
{
	manager.DestroyPrimitive(particlesPrim);
}

void Emiter::RegeneratePrim(int part)
{
	manager.DestroyPrimitive(particlesPrim);
	particlesPrim = manager.NewParticles(part);
	particlesPrim->numParticles = part;
}

void Emiter::Render()
{
	particlesPrim->Update(0, nParts, &(positions[0].x));
}