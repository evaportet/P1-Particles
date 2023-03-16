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

	for (int i = 0; i < nParts; i++)
	{
		positions[i] = glm::vec3(rand() % 5);
		velocities[i] = glm::vec3(rand() % 5);
		accelerations[i] = glm::vec3(0.0f, -0.981f, 0.0f);
	}

	particlesPrim = manager.NewParticles(nParts);
	particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = nParts;
}

ParabolaSim::~ParabolaSim() 
{
	manager.DestroyPrimitive(particlesPrim);
}

void ParabolaSim::Update(float dt) 
{
	totalTime += dt;
	EulerSolver(dt);
	//particlesPrim->Update(0, 1, &(currentPos.x));
}
void ParabolaSim::RenderUpdate() 
{
	/*particlesPrim->firstParticle = 0;
	particlesPrim->numParticles = 100;*/
	particlesPrim->Update(0, nParts, &(positions[0].x));
}
void ParabolaSim::RenderGui() 
{
	
	ImGui::SliderFloat("Emission Rate (particles/s)",
						&emissionRate,
						MIN_EMISSION_RATE,
						MAX_EMISSION_RATE);

	ImGui::SliderFloat("Particle Life (s)",
						&particleLife,
						MIN_LIFE,
						MAX_LIFE);
	
}

void ParabolaSim::EulerSolver(float dt)
{
	for (int i = 0; i < nParts; i++)
	{
		positions[i] = positions[i] + dt * velocities[i];
		velocities[i] = velocities[i] + dt * accelerations[i];
	}

	currentPos = previousPos + dt * currentVel;
	previousPos = currentPos;

	currentVel = previousVel + dt * acceleration;
	previousVel = currentVel;
}