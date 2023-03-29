#include "Emiter.h"

extern graphics::PrimitiveManager manager;

Emiter::Emiter(int em, float pl) : emissionRate(em), particleLife(pl)
{
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

glm::vec3 Emiter::GetParticlePosition(int indice)
{
	return positions[indice];
}

glm::vec3 Emiter::GetParticleVelocity(int indice)
{
	return velocities[indice];
}

glm::vec3 Emiter::GetParticleAcceleration(int indice)
{
	return accelerations[indice];
}

void Emiter::SetParticlePosition(int index, glm::vec3 newP) 
{
	positions[index] = newP;
}

void Emiter::SetParticleVelocity(int index, glm::vec3 newV) 
{
	velocities[index] = newV;
}

void Emiter::SetParticleAcceleration(int index, glm::vec3 newA) 
{
	accelerations[index] = newA;
}

int Emiter::GetNumParticles()
{
	return nParts;
}

void Emiter::Render()
{
	particlesPrim->Update(0, nParts, &(positions[0].x));
}

void Emiter::ToggleVisibility(bool val)
{
	particlesPrim->SetVisible(val);
}