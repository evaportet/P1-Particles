#include <Parabola.h>
#include <PrimitiveManager.h>

extern graphics::PrimitiveManager manager;

ParabolaSim::ParabolaSim() 
{
	currentPos = glm::vec3(0.0f, 0.0f, 0.0f);
	currentVel = glm::vec3(1.0f, 3.0f, 1.0f);
	acceleration = glm::vec3(0.0f, -0.981f, 0.0f);

	previousPos = currentPos;
	previousVel = currentVel;

	totalTime = 0;

	particlesPrim = manager.NewParticles(nParticles);
	particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = nParticles;
}

ParabolaSim::~ParabolaSim() 
{
	manager.DestroyPrimitive(particlesPrim);
}

void ParabolaSim::Update(float dt) 
{
	totalTime += dt;
	EulerSolver(dt);
	particlesPrim->Update(0, 1, &(currentPos.x));
}
void ParabolaSim::RenderUpdate() 
{
	/*particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = 2;
	particlesPrim->Update(0, 2, &(positions[0].x));*/
}
void ParabolaSim::RenderGui() 
{
	/*
	ImGui::SliderFloat("Emission Rate (particles/s)",
						&emissionRate,
						Particles::MIN_EMISSION_RATE,
						Particles::MAX_EMISSION_RATE);

	ImGui::SliderFloat("Particle Life (s)",
						&particleLife,
						Particles::MIN_LIFE,
						Particles::MAX_LIFE);
	*/
}

void ParabolaSim::EulerSolver(float dt)
{
	currentPos = previousPos + dt * currentVel;
	previousPos = currentPos;

	currentVel = previousVel + dt * acceleration;
	previousVel = currentVel;
}